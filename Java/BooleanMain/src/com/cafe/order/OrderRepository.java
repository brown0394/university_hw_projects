package com.cafe.order;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class OrderRepository implements Iterator<Order> {
    List<Order> orders = new ArrayList<>();
    int cur = 0;
    public void add(Order order) {
        if(order != null){
            orders.add(order);
        }
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("---주문 관리자 화면---\n");
        str.append("현재 주문수는 총 " + orders.size() + " 입니다\n\n");
        str.append("<주문 내역>\n");
        for(int i = 0; i < orders.size(); ++i) {
            Order order = orders.get(i);
            str.append("주문번호: " + order.getOrderNo() + " - " + order + "\n");
        }
        return str.toString();
    }

    @Override
    public Order next() {
        if(!orders.isEmpty() && cur < orders.size()){
            Order ord = orders.remove(cur);
            return ord;
        }
        return null;
    }

    @Override
    public boolean hasNext() {
        if (cur < orders.size()) {
            return true;
        }
        return false;
    }
}
