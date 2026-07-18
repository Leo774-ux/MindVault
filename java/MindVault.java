public class MindVault {
    static { System.loadLibrary("mindvault_jni"); }
    public native int init();
    public native int open(String path);
    public native int insert(int id, String data);
    public native String query(int id);
    public native int delete(int id);
    public native void close();
    public native void status();
    public static void main(String[] args) {
        MindVault m = new MindVault();
        System.out.println("init: " + m.init());
        System.out.println("open: " + m.open("/tmp/x.db"));
        System.out.println("insert: " + m.insert(1, "Hi Java!"));
        System.out.println("query: " + m.query(1));
        m.close();
    }
}
