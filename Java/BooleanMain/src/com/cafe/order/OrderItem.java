package com.cafe.order;

import com.cafe.menu.Beverage;

import java.util.Objects;

public class OrderItem {
    Beverage beverage;
    int quantity;

    public OrderItem(Beverage whichone, int howmany){
        beverage = whichone;
        quantity = howmany;
    }

    public void addQuantity(){
        ++quantity;
    }

    @Override
    public String toString() {
        return this.beverage.toString() + ", quantity=" + this.quantity;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        OrderItem orderItem = (OrderItem) o;
        return Objects.equals(beverage, orderItem.beverage);
    }

    @Override
    public int hashCode() {
        return Objects.hash(beverage, quantity);
    }
}
