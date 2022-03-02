//import javax.swing.*;
//import java.awt.*;
//import java.awt.event.*;
//import java.beans.PropertyChangeEvent;
//import java.beans.PropertyChangeListener;
//
//public class SwingDialogView extends JFrame {
//    private JButton button;
//    private JPanel panel;
//    private Font font;
//
//
//    public SwingDialogView() {
//        button = new JButton("Show");
//        panel = new JPanel();
//        setLocationRelativeTo(null);
//        panel.add(button);
//        font = new Font("Serif", Font.PLAIN, 24);
//        button.setFont(font);
//        button.setMnemonic(KeyEvent.VK_S);
//        button.setPreferredSize(new Dimension(380, 255));
//        panel.setPreferredSize(new Dimension(400, 300));
//        setPreferredSize(new Dimension(400,300));
//        SwingDialog dialog = new SwingDialog("Hello");
//
//        button.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                dialog.setVisible(true);
//            }
//        });
//
//
//        add(panel);
//    }
//
//
//}
