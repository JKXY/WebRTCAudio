#include <jni.h>
#include <string>
#include <stdlib.h>

#include "ns/noise_suppression.h"
#include "ns/noise_suppression_x.h"
#include "agc/gain_control.h"
#include "aecm/echo_control_mobile.h"

#if defined(__cplusplus)
extern "C" {
#endif


JNIEXPORT jlong JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_nsCreate(JNIEnv *env, jobject obj) {
    return (long) WebRtcNs_Create();
}


JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_nsInit(JNIEnv *env, jobject obj, jint nsHandler,
                                                    jint frequency) {
    NsHandle *handler = (NsHandle *) nsHandler;
    if (handler == nullptr) {
        return -3;
    }
    return WebRtcNs_Init(handler, frequency);
}


JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_nsSetPolicy(JNIEnv *env, jobject obj, jint
nsHandler, jint mode) {
    NsHandle *handle = (NsHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    return WebRtcNs_set_policy(handle, mode);
}


JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_nsProcess(JNIEnv
                                                       *env,
                                                       jobject obj, jint
                                                       nsHandler,
                                                       jfloatArray spframe, jint num_bands,
                                                       jfloatArray outframe) {
    NsHandle *handle = (NsHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    jfloat *cspframe = env->GetFloatArrayElements(spframe, nullptr);
    jfloat *coutframe = env->GetFloatArrayElements(outframe, nullptr);
    WebRtcNs_Process(handle, &cspframe, num_bands, &coutframe);
    env->ReleaseFloatArrayElements(spframe, cspframe, 0);
    env->ReleaseFloatArrayElements(outframe, coutframe, 0);
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_nsFree(JNIEnv
                                                    *env,
                                                    jobject obj, jlong
                                                    nsHandler) {
    NsHandle *handle = (NsHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    WebRtcNs_Free(handle);
    return 0;
}

JNIEXPORT jlong JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_nsxCreate(JNIEnv *env, jobject obj) {
    return (long) WebRtcNsx_Create();
}


JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_nsxInit(JNIEnv *env, jobject obj, jlong nsHandler,
                                                     jint frequency
) {
    NsxHandle *handler = (NsxHandle *) nsHandler;
    if (handler == nullptr) {
        return -3;
    }
    return WebRtcNsx_Init(handler, frequency);
}


JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_nsxSetPolicy(JNIEnv
                                                          *env,
                                                          jobject obj, jlong
                                                          nsHandler,
                                                          jint mode
) {
    NsxHandle *handle = (NsxHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    return WebRtcNsx_set_policy(handle, mode);
}


JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_nsxProcess(JNIEnv
                                                        *env,
                                                        jobject obj, jlong
                                                        nsHandler,
                                                        jshortArray speechFrame,
                                                        jint num_bands,
                                                        jshortArray outframe) {
    NsxHandle *handle = (NsxHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    jshort *cspeechFrame = env->GetShortArrayElements(speechFrame, nullptr);
    jshort *coutframe = env->GetShortArrayElements(outframe, nullptr);
    WebRtcNsx_Process(handle, &cspeechFrame, num_bands, &coutframe);
    env->ReleaseShortArrayElements(speechFrame, cspeechFrame, 0);
    env->ReleaseShortArrayElements(outframe, coutframe, 0);
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_nsxFree(JNIEnv *env, jobject obj, jlong nsHandler) {
    NsxHandle *handle = (NsxHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    WebRtcNsx_Free(handle);
    return 0;
}


JNIEXPORT jlong JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_aecmCreate(JNIEnv *env, jobject obj) {
    return (jlong) WebRtcAecm_Create();
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_aecmInit(JNIEnv *env,
                                                      jobject obj, jlong aecmInst, jint sampFreq
) {
    void *_aecmInst = (void *) aecmInst;
    if (_aecmInst == nullptr)
        return -3;
    return WebRtcAecm_Init(_aecmInst, sampFreq);
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_aecmFree(JNIEnv *env, jobject obj, jlong aecmInst) {
    void *_aecmInst = (void *) aecmInst;
    if (_aecmInst == nullptr)
        return -3;
    WebRtcAecm_Free(_aecmInst);
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_aecmBufferFarend(JNIEnv *env, jobject obj,
                                                              jlong aecmInst,
                                                              jshortArray farend, jint
                                                              nrOfSamples) {
    void *_aecmInst = (void *) aecmInst;
    if (_aecmInst == nullptr)
        return -3;
    jshort *cfarend = env->GetShortArrayElements(farend, nullptr);
    jint ret = WebRtcAecm_BufferFarend(_aecmInst, cfarend, nrOfSamples);
    env->ReleaseShortArrayElements(farend, cfarend, 0);
    return ret;
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_aecmProcess(JNIEnv
                                                         *env,
                                                         jobject obj, jlong
                                                         aecmInst,
                                                         jshortArray nearendNoisy,
                                                         jshortArray nearendClean,
                                                         jshortArray out,
                                                         jint nrOfSamples,
                                                         jint msInSndCardBuf
) {
    void *_aecmInst = (void *) aecmInst;
    if (_aecmInst == nullptr)
        return -3;
    jshort *cnearendNoisy = env->GetShortArrayElements(nearendNoisy, nullptr);
    jshort *cout = env->GetShortArrayElements(out, nullptr);
    jshort *cnearendClean = nullptr;
    if (nearendClean != nullptr) {
        cnearendClean = env->GetShortArrayElements(nearendClean, nullptr);
    }
    jint ret = WebRtcAecm_Process(_aecmInst, cnearendNoisy, cnearendClean, cout, nrOfSamples,
                                 msInSndCardBuf);
    env->ReleaseShortArrayElements(nearendNoisy, cnearendNoisy, 0);
    if (cnearendClean != nullptr) {
        env->ReleaseShortArrayElements(nearendClean, cnearendClean, 0);
    }
    env->ReleaseShortArrayElements(out, cout, 0);
    return ret;
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_aecmSetConfig(JNIEnv *env, jobject obj, jlong aecmInst,
                                                           jobject config) {
    void *_aecmInst = (void *) aecmInst;
    if (_aecmInst == nullptr)
        return -3;
    jclass JavaAecmConfig = env->GetObjectClass(config);
    assert(JavaAecmConfig != nullptr);
    jfieldID cngModeID = env->GetFieldID(JavaAecmConfig, "cngMode", "S");
    jfieldID echoModeID = env->GetFieldID(JavaAecmConfig, "echoMode", "S");
    if (cngModeID == nullptr || echoModeID == nullptr)
        return -1;
    jshort cngMode = env->GetShortField(config, cngModeID);
    jshort echoMode = env->GetShortField(config, echoModeID);
    AecmConfig setconfig;
    setconfig.echoMode = echoMode;
    setconfig.cngMode = cngMode;
    return WebRtcAecm_set_config(_aecmInst, setconfig);
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_agcCreate(JNIEnv *env, jobject obj) {
    return (long) WebRtcAgc_Create();
}


JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_agcFree(JNIEnv *env, jobject obj, jlong agcInst) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    WebRtcAgc_Free(_agcInst);
    return 0;
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_agcInit(JNIEnv *env,
                                                     jobject obj, jlong agcInst,
                                                     jint minLevel, jint maxLevel,
                                                     jint agcMode, jint fs) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    return WebRtcAgc_Init(_agcInst, minLevel, maxLevel, agcMode, fs);
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_agcSetConfig(JNIEnv  *env, jobject obj, jlong agcInst,
                                                          jobject config
) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    jclass JavaAgcConfig = env->GetObjectClass(config);
    assert(JavaAgcConfig != nullptr);
    jfieldID targetLevelDbfsID = env->GetFieldID(JavaAgcConfig, "targetLevelDbfs", "S");
    jfieldID compressionGaindBID = env->GetFieldID(JavaAgcConfig, "compressionGaindB", "S");
    jfieldID limiterEnableID = env->GetFieldID(JavaAgcConfig, "limiterEnable", "Z");
    if (targetLevelDbfsID == nullptr || compressionGaindBID == nullptr || limiterEnableID == nullptr)
        return -1;
    jshort targetLevelDbfs = env->GetShortField(config, targetLevelDbfsID);
    jshort compressionGaindB = env->GetShortField(config, compressionGaindBID);
    jboolean limiterEnable = env->GetBooleanField(config, limiterEnableID);
    WebRtcAgcConfig setconfig;
    setconfig.targetLevelDbfs = targetLevelDbfs;
    setconfig.compressionGaindB = compressionGaindB;
    setconfig.limiterEnable = limiterEnable;
    return WebRtcAgc_set_config(_agcInst, setconfig);
}

JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_agcProcess(JNIEnv *env, jobject obj, jlong agcInst,
                                                        jshortArray inNear, jint num_bands,
                                                        jint samples, jshortArray out,
                                                        jint inMicLevel, jint outMicLevel,
                                                        jint echo, jboolean saturationWarning) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    jshort *cinNear = env->GetShortArrayElements(inNear, nullptr);
    jshort *cout = env->GetShortArrayElements(out, nullptr);
    jint ret = WebRtcAgc_Process(_agcInst, &cinNear, num_bands, samples, &cout, inMicLevel, &outMicLevel,
                            echo, &saturationWarning);
    env->ReleaseShortArrayElements(inNear, cinNear,0);
    env->ReleaseShortArrayElements(out, cout,0);
    return ret;
}


JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_agcAddFarend(JNIEnv *env, jobject obj, jlong agcInst,
                                                          jshortArray inFar, jint samples) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    short *cinFar = env->GetShortArrayElements( inFar, nullptr);
    jint ret = WebRtcAgc_AddFarend(_agcInst, cinFar, samples);
    env->ReleaseShortArrayElements(inFar, cinFar,0);
    return ret;
}


JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_agcAddMic(JNIEnv *env, jobject obj, jlong agcInst,
                                                       jshortArray inMic, jint num_bands, jint samples
) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    short *cinMic = env->GetShortArrayElements( inMic, nullptr);
    jint ret = WebRtcAgc_AddMic(_agcInst, &cinMic, num_bands, samples);
    env->ReleaseShortArrayElements(inMic, cinMic,0);
    return ret;
}


JNIEXPORT jint JNICALL
Java_com_comone_webrtcaudio_WebRTCAudioUtils_agcVirtualMic(JNIEnv *env, jobject obj, jlong agcInst,
                                                           jshortArray inMic, jint num_bands,
                                                           jint samples, jint micLevelIn,
                                                           jint micLevelOut
) {
    void *_agcInst = (void *) agcInst;
    if (_agcInst == nullptr)
        return -3;
    jshort *cinMic = env->GetShortArrayElements(inMic, nullptr);
    jint ret = WebRtcAgc_VirtualMic(_agcInst, &cinMic, num_bands, samples, micLevelIn, &micLevelOut);
    env->ReleaseShortArrayElements(inMic, cinMic,0);
    return ret;
}

#if defined(__cplusplus)
}
#endif

