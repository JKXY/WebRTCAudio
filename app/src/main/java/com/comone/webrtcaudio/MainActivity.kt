package com.comone.webrtcaudio

import android.media.AudioFormat
import android.media.AudioManager
import android.media.AudioTrack
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.comone.webrtcaudio.WebRTCAudioUtils.AgcConfig
import kotlinx.android.synthetic.main.activity_main.*
import java.io.ByteArrayInputStream
import java.io.ByteArrayOutputStream
import java.io.IOException
import java.nio.ByteBuffer
import java.nio.ByteOrder

class MainActivity : AppCompatActivity() {

    private var isNsx = false
    private var isAgc = false
    private var isAecm = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        nsxView.setOnCheckedChangeListener { _, b -> isNsx = b }
        agcView.setOnCheckedChangeListener { _, b -> isAgc = b }
        aecmView.setOnCheckedChangeListener { _, b -> isAecm = b }
        auidioInit()
        startView.setOnClickListener {
            startAudiodProcess()
        }

    }

    private val audioRes by lazy {
        resources.openRawResource(R.raw.xftest)
    }

    private val audioUtils by lazy {
        WebRTCAudioUtils()
    }

    private var nsxInst = -1L
    private var agcInst = -1L
    private var aecmInst = -1L

    private fun auidioInit() {
        nsxInst = audioUtils.nsxCreate()
        val nsxInit = audioUtils.nsxInit(nsxInst, 16000)
        val nexSetPolicy = audioUtils.nsxSetPolicy(nsxInst, 2)

        Log.e(localClassName, "nsxInst : $nsxInst  nsxInit: $nsxInit nexSetPolicy: $nexSetPolicy")

        agcInst = audioUtils.agcCreate()
        val agcInit = audioUtils.agcInit(agcInst, 0, 255, 3, 16000)
        val agcSetConfig = audioUtils.agcSetConfig(agcInst, audioUtils.getAgcConfig(9, 9, true))

        Log.e(localClassName, "agcInst : $agcInst  agcInit: $agcInit agcSetConfig: $agcSetConfig")


        aecmInst = audioUtils.aecmCreate()
        val aecmInit = audioUtils.aecmInit(aecmInst, 16000)
        val aecmConfig = audioUtils.aecmSetConfig(aecmInst, audioUtils.getAecmConfig(1, 3))

        Log.e(localClassName, "aecmInst : $aecmInst  aecmInit: $aecmInit aecmConfig: $aecmConfig")

    }

    private fun startAudiodProcess() {
        _stopReplay()
        mAudio.reset()
        audioRes.reset()
        val audioData = audioRes.readBytes()
        audioData.asSequence().chunked(320).filter { it.size == 320 }.forEach {
            val inputData = ShortArray(160)
            val outNsData = ShortArray(160)
            val outAgcData = ShortArray(160)
            val outAecmData = ShortArray(160)
            ByteBuffer.wrap(it.toByteArray()).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer()
                .get(inputData)
            if (isNsx)
                audioUtils.nsxProcess(nsxInst, inputData, 1, outNsData)
            if (isAgc) {
                audioUtils.agcProcess(agcInst,
                    if (isNsx) outNsData else inputData,
                    1,160,outAgcData,0,0,0,false
                )
            }
            if (isAecm) {
                audioUtils.aecmBufferFarend(
                    aecmInst,
                    if (isAgc) outAgcData
                    else if (isNsx) outNsData
                    else inputData
                    , 160
                )
                audioUtils.aecmProcess(
                    aecmInst,
                    if (isAgc) outAgcData
                    else if (isNsx) outNsData
                    else inputData
                    , null, outAecmData, 160, 100
                )
            }

            if (isAecm)
                mAudio.write(audioUtils.shortArrayToByteArry(outAecmData))
            else if (isAgc)
                mAudio.write(audioUtils.shortArrayToByteArry(outAgcData))
            else if (isNsx)
                mAudio.write(audioUtils.shortArrayToByteArry(outNsData))
            else
                mAudio.write(it.toByteArray())
        }
        _startReplay()
    }


    private var _isReplaying = false
    private val mAudio = ByteArrayOutputStream()
    private val mPlayProc = Runnable {
        val play = AudioTrack(
            AudioManager.STREAM_MUSIC,
            16000,
            AudioFormat.CHANNEL_OUT_MONO,
            AudioFormat.ENCODING_PCM_16BIT,
            _recordBufferSize,
            AudioTrack.MODE_STREAM
        )
        play.play()
        try {
            ByteArrayInputStream(mAudio.toByteArray()).use { f ->
                val buf = ByteArray(_recordBufferSize)
                while (true) {
                    if (Thread.interrupted())
                        throw InterruptedException()
                    val m = f.read(buf)
                    if (m <= 0)
                        break
                    play.write(buf, 0, m)
                }
                play.flush()
                while (play.playState == AudioTrack.PLAYSTATE_PLAYING) {
                    if (Thread.interrupted())
                        throw InterruptedException()
                    Thread.sleep(100)
                }
            }
        } catch (e: InterruptedException) {
            play.stop()
        } catch (e: IOException) {
            e.printStackTrace()
            play.stop()

        }
        play.release()
    }


    private val _recordBufferSize by lazy {
        AudioTrack.getMinBufferSize(
            16000,
            AudioFormat.CHANNEL_OUT_MONO,
            AudioFormat.ENCODING_PCM_16BIT
        )
    }

    private var mPlayThread: Thread? = null
    private fun _startReplay() {
        _isReplaying = true
        if (mPlayThread == null) {
            mPlayThread = Thread(mPlayProc)
            mPlayThread?.start()
        }
    }

    private fun _stopReplay() {
        _isReplaying = false
        if (mPlayThread != null) {
            mAudio.reset()
            mPlayThread?.interrupt()
            try {
                mPlayThread?.join()
            } catch (e: InterruptedException) {
            }
            mPlayThread = null
        }
    }

    override fun onPause() {
        super.onPause()
        audioUtils.nsxFree(nsxInst)
        audioUtils.agcFree(agcInst)
        audioUtils.aecmFree(aecmInst)
        _stopReplay()
    }

}
