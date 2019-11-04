#include <jni.h>
#include <fluidsynth.h>

fluid_settings_t *settings;
fluid_synth_t *synth;
fluid_audio_driver_t *adriver;

const int CHAN_LEVEL_CC=0x07;

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_init(
        JNIEnv *env,
        jobject /* this */,
        jstring sf2path) {
    // Init settings
    settings = new_fluid_settings();
    fluid_settings_setstr(settings, "audio.driver", "opensles");
    fluid_settings_setint(settings, "audio.opensles.use-callback-mode", 1);
    fluid_settings_setint(settings, "audio.periods", 2);
    fluid_settings_setint(settings, "synth.sample-rate", 44100);

    fluid_settings_setint(settings, "audio.period-size", 128);

    synth = new_fluid_synth(settings);

    // Init soundfont
    const char *nativeSf2Path = env->GetStringUTFChars(sf2path, nullptr);
    fluid_synth_sfload(synth, nativeSf2Path, true);
    env->ReleaseStringUTFChars(sf2path, nativeSf2Path);

    adriver = new_fluid_audio_driver(settings, synth);
}

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_noteOn(
        JNIEnv *env,
        jobject /* this */,
        jint channel,
        jint key,
        jint velocity) {
    fluid_synth_noteon(synth, channel, key, velocity);
}

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_noteOff(
        JNIEnv *env,
        jobject /* this */,
        jint channel,
        jint key) {
    fluid_synth_noteoff(synth, channel, key);
}

extern "C"
JNIEXPORT jboolean JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_programChange(
        JNIEnv *env,
        jobject /* this */,
        jint channel,
        jint programNumber) {
    return (jboolean) (FLUID_OK == fluid_synth_program_change(synth, (int) channel, (int) programNumber));
}

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_destroy(
        JNIEnv *env,
        jobject /* this */) {
    delete_fluid_audio_driver(adriver);
    delete_fluid_synth(synth);
    delete_fluid_settings(settings);
}

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_synthGainLevel(
        JNIEnv *env,
        jobject /* this */,
        jfloat gain) {

     fluid_settings_setnum(settings, "synth.gain", (float) gain);

}



extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_channelLevel(
        JNIEnv *env,
        jobject /* this */,
        jint channel,
        jint level) {
    fluid_synth_cc(synth,(int) channel, CHAN_LEVEL_CC, int(level));
}

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_midiCC(
        JNIEnv *env,
        jobject /* this */,
        jint channel,
        jint ctrl,
        jint value) {
    fluid_synth_cc(synth,(int) channel, ctrl, int(value));
}

extern "C"
JNIEXPORT void JNICALL Java_opensles_android_fluidsynth_fluidsynth_1android_1opensles_NativeLibJNI_pitchBend(
        JNIEnv *env,
        jobject /* this */,
        jint channel,
        jint value) {
    fluid_synth_pitch_bend(synth,(int) channel, int(value));
}

