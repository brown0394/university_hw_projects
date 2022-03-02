//import javax.swing.*;
//import java.awt.*;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//
//public class ButtonView extends JFrame {
//    public ButtonView() {
//        this.setLayout(new FlowLayout());
//        setSize(400, 150);
//        JButton button_disable = new JButton("Disable middle button");
//        JButton button_middle = new JButton("Middle button");
//        JButton button_enable = new JButton("Enable middle button");
//        button_enable.setEnabled(false);
//        button_disable.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                button_middle.setEnabled(false);
//                button_disable.setEnabled(false);
//                button_enable.setEnabled(true);
//            }
//        });
//        button_enable.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                button_middle.setEnabled(true);
//                button_disable.setEnabled(true);
//                button_enable.setEnabled(false);
//            }
//        });
//        JFrame frame = this;
//        button_middle.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                JOptionPane.showMessageDialog(frame, "dialog");
//            }
//        });
//
//        getContentPane().add(button_disable, BorderLayout.WEST);
//        getContentPane().add(button_middle, BorderLayout.CENTER);
//        getContentPane().add(button_enable, BorderLayout.EAST);
//    }
//}
