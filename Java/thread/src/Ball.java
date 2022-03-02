//import java.awt.geom.Ellipse2D;
//import java.awt.geom.Rectangle2D;
//import java.util.concurrent.ThreadLocalRandom;
//
//class Ball {
//    public void move(Rectangle2D bounds) { // java.awt.geom.Rectangle2D
//        dx = ThreadLocalRandom.current().nextDouble(0, 10) * directionX;
//        dy = ThreadLocalRandom.current().nextDouble(0, 10) * directionY;
//        x += dx; y += dy;
//        if (x < bounds.getMinX()) {  x = bounds.getMinX(); directionX = -directionX; }
//        if (x + XSIZE >= bounds.getMaxX()) { x = bounds.getMaxX() - XSIZE;  directionX= -directionX;  }
//        if (y < bounds.getMinY()) { y = bounds.getMinY();  directionY = -directionY; }
//        if (y + YSIZE >= bounds.getMaxY()) { y = bounds.getMaxY() - YSIZE; directionY = -directionY; }
//    }
//    public Ellipse2D getShape() { return new Ellipse2D.Double(x, y, XSIZE, YSIZE); }
//
//    private static final int XSIZE = 15;
//    private static final int YSIZE = 15;
//    private double x = ThreadLocalRandom.current().nextDouble(0, 15) ;
//    private double y = ThreadLocalRandom.current().nextDouble(0, 15);
//    private double dx = 1;
//    private double dy = 1;
//    private double directionX = 1.0d;
//    private double directionY = 1.0d;
//}