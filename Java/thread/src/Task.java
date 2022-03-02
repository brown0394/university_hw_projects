import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Task extends SwingWorker<Void, Void> {
    private JProgressBar progressBar;
    private JButton startButton;
    private JTextArea taskOutput;
    private JPanel panel;
    public Task(JProgressBar progressBar ,JButton startButton ,JTextArea taskOutput, JPanel p) {
        this.progressBar = progressBar;
        this.startButton = startButton;
        this.taskOutput = taskOutput;
        this.panel = p;
    }
    public Void doInBackground() { // executed in worker thread
        Random random = new Random();
        int progress = 0;
        setProgress(0); // Initialize progress property.
        while (progress < 100) {
// Sleep for up to one second.
            try {
                Thread.sleep(random.nextInt(1000));
            } catch (InterruptedException e) { }
// Make random progress
            progress += random.nextInt(10);
            setProgress(Math.min(progress, 100));
        }
        return null;
    }
    public void done() { // executed in Event Dispatch Thread
        Toolkit.getDefaultToolkit().beep();
        startButton.setEnabled(true);
        panel.setCursor(null); // turn off the wait cursor
        taskOutput.append("Done!\n");
    }
}
