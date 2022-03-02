//package edu.pnu.collection;
//
//import java.util.Arrays;
//
//public class GenericList<T> {
//    private static final int DEFAULT_SIZE = 10;
//    private Object[] data;
//    private int size = 0;
//    private int limit = DEFAULT_SIZE;
//
//    public GenericList() {
//        data = new Object[DEFAULT_SIZE];
//    }
//
//    public GenericList(int lim) {
//        limit = lim;
//        data = new Object[limit];
//    }
//
//    public int size() {
//        return this.size;
//    }
//    public T get(int i) {
//        T value = null;
//        if (this.size > i){
//            value = (T)data[i];
//        }
//        return value;
//    }
//
//    public void add(T newelement) {
//        if (size == limit) {
//            limit += DEFAULT_SIZE;
//            Object[] newarr = new Object[limit];
//            for (int i = 0; i < data.length; ++i) {
//                newarr[i] = data[i];
//            }
//            newarr[size++] = newelement;
//            data = newarr;
//        }
//        else {
//            data[size++] = newelement;
//        }
//    }
//
//    public boolean isEmpty() {
//        return size == 0;
//    }
//
//    public void clear() {
//        size = 0;
//        limit = DEFAULT_SIZE;
//        data = new Object[DEFAULT_SIZE];
//    }
//}
