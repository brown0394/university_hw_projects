package com.cafe.menu;

import java.util.Objects;

public abstract class Beverage {
    enum SIZE{TALL, GRANDE, VENTI}

    String name; int basePrice; SIZE size;

    public Beverage(String n, int price, SIZE s){
        name = n;
        basePrice = price;
        size = s;
    }

    public int getPrice(){
//        if(size > 0){
//            return this.basePrice + (size * 500);
//        }
        return this.basePrice;
    }

    public boolean setSize(SIZE size){
        this.size = size;
        return true;
    }

//    public boolean setSize(String size){
//        if ("TALL".equals(size))
//            return setSize(SIZE.TALL);
//        else if ("GRANDE".equals(size))
//            return setSize(SIZE.GRANDE);
//        else if ("VENTI".equals(size))
//            return setSize(SIZE.VENTI);
//        return false;
//    }

    @Override
    public String toString() {
        return "name=" + name +
                ", Price=" + getPrice() +
                ", size=" + size.name();
    }

    public boolean equals(String name) {
        if (name == null ) return false;
        return Objects.equals(this.name, name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, basePrice, size);
    }
}
