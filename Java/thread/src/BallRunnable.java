//import javax.swing.*;
//
//class BallRunnable implements Runnable {
//    public BallRunnable(Ball aBall, JPanel ballPanel) {
//        ball = aBall;  this.ballPanel = ballPanel;
//    }
//    public void run() {
//        try {
//            for (int i = 1; i <= STEPS; i++) {
//                ball.move(ballPanel.getBounds()); // update the location of the ball
//                ballPanel.paint(ballPanel.getGraphics());
//                Thread.sleep(DELAY);
//            }
//        } catch (InterruptedException e) { e.printStackTrace();}
//    }
//    private Ball ball;
//    private JPanel ballPanel;
//    public static final int STEPS = 1000;
//    public static final int DELAY = 16;
//}
