package com.cafe.order;

import com.cafe.menu.Blended;
import com.cafe.menu.Coffee;
import com.cafe.menu.Teavana;
import com.cafe.order.Order;
import com.cafe.order.OrderItem;
import com.cafe.order.OrderRepository;
import com.cafe.order.PickUpFactory;

public class OrderTest {
    static PickUpFactory pickUpFactory = new PickUpFactory();
    public static void main(String[] args) {
        OrderRepository orderRepository = new OrderRepository();

        orderRepository.add(makeOrderForDelivery());
        orderRepository.add(makeOrderForDriveThru());
        orderRepository.add(makeOrderForTakeOut());

        while(orderRepository.hasNext()) {
            System.out.println(orderRepository);
            Order order = orderRepository.next();
            if (order == null) break;
            order.completed();
        }
    }

    private static Order makeOrderForTakeOut() {
        Order order = new Order();
        Order.PickUp pickUp = pickUpFactory.makeTakeOut();
        order.setPickUp(pickUp);
        order.addItem(new OrderItem(new Teavana("Chamomile"), 1)) ;
        order.addItem(new OrderItem(new Coffee("Americano"), 1)) ;
        return order;
    }

    private static Order makeOrderForDriveThru() {
        Order order = new Order();
        Order.PickUp pickUp = pickUpFactory.makeDriveThru("001가0000");
        order.setPickUp(pickUp);
        order.addItem(new OrderItem(new Coffee("Americano"), 2)) ;
        return order;
    }

    private static Order makeOrderForDelivery() {
        Order order = new Order();
        Order.PickUp pickUp = pickUpFactory.makeDelivery("Pusan National University");
        order.setPickUp(pickUp);
        order.addItem(new OrderItem(new Blended("MangoBanana"), 1)) ;
        order.addItem(new OrderItem(new Coffee("Americano"), 1)) ;
        return order;
    }
}