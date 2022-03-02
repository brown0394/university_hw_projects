import javax.swing.*;
import java.awt.*;

public class ProgressBarTest extends JPanel{
    private static JProgressBar progressBar;
    private static JButton startButton;
    private static JTextArea taskOutput;
    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                createAndShowGUI();
            }
        });
    }
    private static void createAndShowGUI() {
        JPanel panel = new JPanel();
        JFrame frame = new JFrame("ProgressBarDemo");
//        panel.add(startButton); panel.add(progressBar);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //add(panel, BorderLayout.PAGE_START);
        JComponent newContentPane = new ProgressBarView();
        //add(new JScrollPane(taskOutput),BorderLayout.CENTER);
        newContentPane.setOpaque(true);
        frame.setContentPane(newContentPane);
        //setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
        frame.pack();
        frame.setVisible(true);
    }
}