//import javax.swing.*;
//
//import java.awt.*;
//import java.util.ArrayList;
//import java.util.List;
//import java.util.concurrent.CopyOnWriteArrayList;
//
//class BallPanel extends JPanel {
//    public void add (Ball b) {
//        //System.out.println("add: " + Thread.currentThread().getName());
//        balls.add(b);
//    }
//    public void paintComponent (Graphics g) {
//        super.paintComponent(g);
//        Graphics2D g2 = (Graphics2D) g;
//        //System.out.println("paintComponent: " + Thread.currentThread().getName());
//        for (Ball b : balls) { g2.fill(b.getShape()); }
//    }
//    //private List<Ball> balls = new ArrayList<>();
//    CopyOnWriteArrayList<Ball> balls = new CopyOnWriteArrayList<>();
//}