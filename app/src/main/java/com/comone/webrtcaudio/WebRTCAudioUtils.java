package com.comone.webrtcaudio;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class WebRTCAudioUtils {
    static {
        System.loadLibrary("native-lib");
    }

    public native long nsCreate();

    public native int nsInit(long nsHandler, int frequency);

    public native int nsSetPolicy(long nsHandler, int mode);

    public native int nsProcess(long nsHandler, float[] spframe, int num_bands,float[] outframe);

    public native int nsFree(long nsHandler);


    public native long nsxCreate();

    public native int nsxInit(long nsxHandler, int frequency);

    public native int nsxSetPolicy(long nsxHandler, int mode);

    public native int nsxProcess(long nsxHandler, short[] speechFrame, int num_bands,short[] outframe);

    public native int nsxFree(long nsxHandler);


    public native long aecmCreate();

    public native int aecmInit(long aecmInst, int sampFreq);

    public native int aecmFree(long aecmInst);

    public native int aecmBufferFarend(long aecmInst, short[] farend, int nrOfSamples);

    public native int aecmProcess(long aecmInst, short[] nearendNoisy, short[] nearendClean, short[] out, int nrOfSamples, int msInSndCardBuf);

    public class AecmConfig {
        private short cngMode;
        private short echoMode;

        public AecmConfig(short cngMode, short echoMode) {
            this.cngMode = cngMode;
            this.echoMode = echoMode;
        }
    }

    public AecmConfig getAecmConfig(short cngMode, short echoMode){
        return new AecmConfig(cngMode, echoMode);
    }

    public native int aecmSetConfig(long aecmInst, AecmConfig config);


    public native long agcCreate();

    public native int agcFree(long agcInst);

    public native int agcInit(long agcInst, int minLevel, int maxLevel, int agcMode, int fs);

    public class AgcConfig {
        private short targetLevelDbfs;
        private short compressionGaindB;
        private boolean limiterEnable;

        public AgcConfig(short targetLevelDbfs, short compressionGaindB, boolean limiterEnable) {
            this.targetLevelDbfs = targetLevelDbfs;
            this.compressionGaindB = compressionGaindB;
            this.limiterEnable = limiterEnable;
        }
    }

    public AgcConfig getAgcConfig(short targetLevelDbfs, short compressionGaindB, boolean limiterEnable){
        return new AgcConfig(targetLevelDbfs,compressionGaindB,limiterEnable);
    }

    public native int agcSetConfig(long agcInst, AgcConfig config);

    public native int agcProcess(long agcInst, short[] inNear,int num_bands,int samples,short[] out,
                                 int inMicLevel,int outMicLevel,int echo,boolean saturationWarning);

    public native int agcAddFarend(long agcInst,short[] inFar,int samples);

    public native int agcAddMic(long agcInst,short[] inMic,int num_bands,int samples);

    public native int agcVirtualMic(long agcInst,short[] inMic,int num_bands,int samples,int micLevelIn,int micLevelOut);



    public short[] byetArrayToShortArray(byte[] data) {
        short[] outDataend = new short[data.length / 2];
        ByteBuffer.wrap(data).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().get(outDataend);
        return outDataend;
    }

    // shortArraytobyteArray
    public byte[] shortArrayToByteArry(short[] data) {
        byte[] byteVal = new byte[data.length * 2];
        for (int i = 0; i < data.length; i++) {
            byteVal[i * 2] = (byte) (data[i] & 0xff);
            byteVal[i * 2 + 1] = (byte) ((data[i] & 0xff00) >> 8);
        }
        return byteVal;
    }
}
