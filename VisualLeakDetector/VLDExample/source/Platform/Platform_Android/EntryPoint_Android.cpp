#ifdef _PLATFORM_ANDROID

#include <string.h>
#include <jni.h>

#include "Platform.h"
#include "Platform_Android.h"

JNIEnv* _env;

extern "C"
{
	JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnCreate( JNIEnv* env, jobject jObj );
	JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnSurfaceCreated( JNIEnv* env, jobject jObj );
	JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnSurfaceChanged( JNIEnv* env, jobject jObj, jint width, jint height );
    JNIEXPORT int Java_tile_swap_flowers_puzzle_MyView_jniOnDrawFrame( JNIEnv* env, jobject jObj, jint deltaTimeInMillis );
    JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnTouchEvent( JNIEnv* env, jobject jObj, jint x, jint y, jint eventID );
    JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnPause( JNIEnv* env, jobject jObj );
    JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnResume( JNIEnv* env, jobject jObj );
    JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnStop( JNIEnv* env, jobject jObj );
    JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnDestroy( JNIEnv* env, jobject jObj );
    JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniSetAssetManager(JNIEnv* env, jobject jobj, jobject assetManager);
    JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniSetSaveFolderPath(JNIEnv* env, jobject jobj, jstring saveFolderPath);
    JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniSetLanguageID(JNIEnv* env, jobject jobj, jint languageID);
    JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniSetBackKeyPressed(JNIEnv* env, jobject jobj);

};

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnCreate( JNIEnv* env, jobject jObj )
{
	Platform::GetPlatform()->onCreate();
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnSurfaceCreated( JNIEnv* env, jobject jObj )
{
	//Platform::GetPlatform()->onCreate();
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniSetAssetManager(JNIEnv* env, jobject jobj, jobject assetManager)
{
	Platform_Android* platformAndroid = (Platform_Android*)Platform::GetPlatform();
	platformAndroid->SetAssetManager( AAssetManager_fromJava(env, assetManager) );
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnSurfaceChanged( JNIEnv* env, jobject jObj, jint width, jint height )
{

	Platform::GetPlatform()->onSizeChange(width, height);
}

JNIEXPORT int Java_tile_swap_flowers_puzzle_MyView_jniOnDrawFrame( JNIEnv* env, jobject jObj, jint deltaTimeInMillis )
{
	_env = env;
	return Platform::GetPlatform()->Draw(deltaTimeInMillis);
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnTouchEvent( JNIEnv* env, jobject jObj, jint x, jint y, jint eventID )
{
	Platform::GetPlatform()->onTouch(x, y, eventID);
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnPause( JNIEnv* env, jobject jObj )
{
	Platform::GetPlatform()->onPause();
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnResume( JNIEnv* env, jobject jObj )
{
	Platform::GetPlatform()->onResume();
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnStop( JNIEnv* env, jobject jObj )
{
	Platform::GetPlatform()->onPause();
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniOnDestroy( JNIEnv* env, jobject jObj )
{
	Platform::GetPlatform()->onExit();
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniSetSaveFolderPath(JNIEnv* env, jobject jobj, jstring saveFolderPath)
{
	const char *path = env->GetStringUTFChars(saveFolderPath, NULL);
	Platform::GetPlatform()->SetSaveFolderPath(path);
	env->ReleaseStringUTFChars(saveFolderPath, path);
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniSetLanguageID(JNIEnv* env, jobject jobj, jint languageID)
{
	Platform_Android* platformAndroid = (Platform_Android*)Platform::GetPlatform();
	platformAndroid->SetLanguageID(languageID);
}

JNIEXPORT void Java_tile_swap_flowers_puzzle_MyView_jniSetBackKeyPressed(JNIEnv* env, jobject jobj)
{
	Platform::GetPlatform()->SetBackKeyPressed();
}

//Callbacks to JAVA

void PlayMusic_native(bool variable)
{
	jclass classID = (_env)->FindClass("tile/swap/flowers/puzzle/MyView");
	jmethodID methodID = (_env)->GetStaticMethodID(classID, "PlayMusic", "(Z)V");
	(_env)->CallStaticVoidMethod(classID, methodID, variable);
}

bool IsMusicPlaying_native()
{
	jclass cls = (_env)->FindClass("tile/swap/flowers/puzzle/MyView");
	jmethodID mid = (_env)->GetStaticMethodID(cls, "IsMusicPlaying", "()Z");
	return (_env)->CallStaticBooleanMethod(cls, mid, 0);
}

float GetTimeInSeconds_native()
{
	jclass cls = (_env)->FindClass("tile/swap/flowers/puzzle/MyView");
	jmethodID mid = (_env)->GetStaticMethodID(cls, "GetTimeInSeconds", "()F");
	return (_env)->CallStaticBooleanMethod(cls, mid, 0);
}

int GetTimeInMillis_native()
{
	jclass cls = (_env)->FindClass("tile/swap/flowers/puzzle/MyView");
	jmethodID mid = (_env)->GetStaticMethodID(cls, "GetTimeInMillis", "()I");
	return (_env)->CallStaticBooleanMethod(cls, mid, 0);
}

void ShowMsg_native(char* arr)
{
	jstring jStr = (_env)->NewStringUTF(arr);
	jclass cls = (_env)->FindClass("tile/swap/flowers/puzzle/MyView");
	jmethodID mid = (_env)->GetStaticMethodID(cls, "ShowMsg", "(Ljava/lang/String;)V");
	(_env)->CallStaticBooleanMethod(cls, mid, jStr);
}


#endif
