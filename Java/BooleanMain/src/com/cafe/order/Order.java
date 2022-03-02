package com.cafe.order;
import java.util.ArrayList;
import java.util.List;

public class Order {
    private List<OrderItem> items = new ArrayList<>();

    private static int orderCounter = 1;
    private int orderNo;

    private Order.PickUp delivery;

    public Order() {
        this.orderNo = orderCounter++;
    }

    public static interface PickUp {
        public abstract void handle(Order o);
    }

    public void completed() {
        delivery.handle(this);
    }

    public void setPickUp(PickUp pick) {
        if(pick != null) {
            this.delivery = pick;
        }
    }

    int getOrderNo() {
        return this.orderNo;
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("[");
        boolean first = true;
        for(OrderItem e : items) {
            if(first) {
                first = false;
            }
            else {
                str.append(", ");
            }
            str.append(e);
        }
        str.append("]");
        return str.toString();
    }

    public void addItem(OrderItem item) {
        if (item != null) {
            items.add(item);
        }
    }

//    public int cost() {
//        int total = 0;
//        if (!items.isEmpty()) {
//            for (OrderItem e : items) {
//                total += (e.beverage.getPrice() * e.quantity);
//            }
//        }
//        return total;
//    }
}
//    public boolean setSize(String name, String size) {
//        if (!items.isEmpty()) {
//            for (OrderItem o : items) {
//                if (o.beverage.equals(name)) {
//                    return o.beverage.setSize(size);
//                }
//            }
//        }
//        return false;
//    }

//    public void print() {
//        int total = 0;
//        if (!this.items.isEmpty()) {
//            for (OrderItem o : items) {
//                System.out.println(o);
//                total += (o.beverage.getPrice() * o.quantity);
//            }
//        }
//        System.out.printf("Total: %,d%n", total);
//    }
//}
