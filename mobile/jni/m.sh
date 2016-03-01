#! /bin/bash -e

export PATH=$PATH:/home/irdetogame/opt/android-ndk-r9d/toolchains/arm-linux-androideabi-4.8/prebuilt/linux-x86/bin:/home/irdetogame/opt/android-ndk-r9d
if [[ $2 == 1 ]]; then
cd xcode
make cloaked $1=on
cd ..
$NDK_ROOT/ndk-build -B $1=on
cp ../obj/local/armeabi/libmg.a libmg_armeabi_$1_r.a
cp ../obj/local/x86/libmg.a libmg_x86_$1_r.a
fi
if [[ $2 == 0 ]]; then
$NDK_ROOT/ndk-build -B $1=on ANDROID_DEBUG=on
cp /home/irdetogame/dillon/work/crypto/mobile/obj/local/armeabi/libmg.a libmg_armeabi_$1_d.a
cp /home/irdetogame/dillon/work/crypto/mobile/obj/local/x86/libmg.a libmg_x86_$1_d.a
fi
