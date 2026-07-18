#include <jni.h>
#include "../java/MindVault.h"
#include "mindvault.h"

JNIEXPORT jint JNICALL Java_MindVault_init(JNIEnv* e, jobject o) { return mv_init(); }
JNIEXPORT jint JNICALL Java_MindVault_open(JNIEnv* e, jobject o, jstring p) {
    const char* s = (*e)->GetStringUTFChars(e, p, 0);
    int r = mv_open(s);
    (*e)->ReleaseStringUTFChars(e, p, s);
    return r;
}
JNIEXPORT jint JNICALL Java_MindVault_insert(JNIEnv* e, jobject o, jint id, jstring d) {
    const char* s = (*e)->GetStringUTFChars(e, d, 0);
    int r = mv_insert(id, s);
    (*e)->ReleaseStringUTFChars(e, d, s);
    return r;
}
JNIEXPORT jstring JNICALL Java_MindVault_query(JNIEnv* e, jobject o, jint id) {
    Record* r = mv_query(id);
    return (*e)->NewStringUTF(e, r ? r->data : "null");
}
JNIEXPORT jint JNICALL Java_MindVault_delete(JNIEnv* e, jobject o, jint id) { return mv_delete(id); }
JNIEXPORT void JNICALL Java_MindVault_close(JNIEnv* e, jobject o) { mv_close(); }
JNIEXPORT void JNICALL Java_MindVault_status(JNIEnv* e, jobject o) { mv_status(); }
