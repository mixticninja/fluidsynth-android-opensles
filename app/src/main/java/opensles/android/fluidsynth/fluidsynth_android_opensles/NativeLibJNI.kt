package opensles.android.fluidsynth.fluidsynth_android_opensles

class NativeLibJNI {
    external fun init(sf2path: String)
    external fun noteOn(channel: Int, key: Int, velocity: Int)
    external fun noteOff(channel :Int,key: Int)
    external fun programChange(channel: Int, programNumber: Int) : Boolean
    external fun synthGainLevel(gain :Float)
    external fun channelLevel(channel:Int, vol: Int)
    external fun midiCC(channel:Int,ctrl:Int, value: Int)
    external fun pitchBend(channel:Int, value: Int)
    external fun destroy()
}