//import javax.swing.*;
//import java.awt.*;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//
//class BounceBallView extends JFrame {
//    public BounceBallView() {
//        setTitle("Bounce");
//        setSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
//        ballPanel = new BallPanel(); add(ballPanel, BorderLayout.CENTER);
//        JPanel buttonPanel = new JPanel();
//        addButton(buttonPanel, "Start", new ActionListener() {
//            public void actionPerformed(ActionEvent event) { addRunnableBall(); }
//        });
//        addButton(buttonPanel, "Close", new ActionListener() {
//            public void actionPerformed(ActionEvent event) { System.exit(0); }
//        });
//        add(buttonPanel, BorderLayout.SOUTH);
//    }
//    private void addButton(Container container, String title, ActionListener listener) {
//        JButton button = new JButton(title);
//        container.add(button);
//        button.addActionListener(listener);
//    }
//    private void addRunnableBall() {
//        Ball b = new Ball();
//        ballPanel.add(b);
//        Runnable r = new BallRunnable(b, ballPanel);
//        Thread t = new Thread(r);
//        t.start();
//    }
//    private BallPanel ballPanel;
//    public static final int DEFAULT_WIDTH = 450;
//    public static final int DEFAULT_HEIGHT = 350;
//    public static final int STEPS = 1000;
//    public static final int DELAY = 100;
//}
