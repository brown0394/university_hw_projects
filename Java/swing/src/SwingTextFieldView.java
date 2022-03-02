//import javax.swing.*;
//import javax.swing.border.EtchedBorder;
//import java.awt.*;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//
//public class SwingTextFieldView extends JFrame {
//    JTextField textField;
//    JTextArea textArea;
//    public SwingTextFieldView() {
//        textField = new JTextField(20);
//        Font font = new Font(textField.getFont().getName(),
//                textField.getFont().getStyle(), 15);
//        textField.setFont(font);
//        textField.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                String text = textField.getText();
//                textArea.append(text + "\n");
//                textField.selectAll();
//                textArea.setCaretPosition(textArea.getDocument().getLength());
//            }
//        });
//
//        textArea = new JTextArea(5, 20);
//        textArea.setFont(font);
//        textArea.setEditable(false);
//        JScrollPane scrollPane = new JScrollPane(textArea);
//
//        JButton buttonEnter = new JButton("Enter");
//        buttonEnter.addActionListener(new ActionListener() {
//            @Override
//            public void actionPerformed(ActionEvent e) {
//                String text = textField.getText();
//                textArea.append(text + "\n");
//                textField.selectAll();
//                textArea.setCaretPosition(textArea.getDocument().getLength());
//            }
//        });
//        JPanel panel1 = new JPanel();
//        panel1.setLayout(new FlowLayout());
//        panel1.add(textField);
//        panel1.add(buttonEnter);
//        //setLayout(new BorderLayout(5, 5));
//        add(panel1, BorderLayout.NORTH);
//        add(scrollPane, BorderLayout.SOUTH);
//    }
//}
