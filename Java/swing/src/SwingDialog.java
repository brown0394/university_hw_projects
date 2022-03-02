//import javax.swing.*;
//import java.awt.*;
//import java.awt.event.*;
//import java.beans.PropertyChangeEvent;
//import java.beans.PropertyChangeListener;
//
//public class SwingDialog extends JDialog implements ActionListener, PropertyChangeListener {
//    private String magicWord;
//    private String typedText;
//    private JOptionPane optionPane;
//    private JTextField textField;
//    private Font font;
//
//    protected SwingDialog(String word) {
//        this.magicWord = word.toUpperCase();
//        font = new Font("Serif", Font.PLAIN, 24);
//        setTitle("Quiz");
//        textField = new JTextField(10);
//        textField.setFont(font);
//        String msg = "What was Dr. SEUSS's" +
//                " real last name?\n(The answer is \"" + word + "\".)";
//        Object[] array = {msg, textField};
//        Object[] options = {"Enter", "Cancel"};
//        UIManager.put("OptionPane.messageFont", font);
//        UIManager.put("OptionPane.buttonFont", font);
//
//        optionPane = new JOptionPane(array, JOptionPane.QUESTION_MESSAGE,
//                JOptionPane.YES_NO_OPTION, null, options, options[0]);
//        setContentPane(optionPane);
//        setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
//        addWindowListener(new WindowAdapter() {
//            @Override
//            public void windowClosing(WindowEvent e) {
//                optionPane.setValue(new Integer(JOptionPane.CLOSED_OPTION));
//            }
//        });
//        addComponentListener(new ComponentAdapter() {
//            @Override
//            public void componentShown(ComponentEvent e) {
//                textField.requestFocusInWindow();
//            }
//        });
//        textField.addActionListener(this);
//        optionPane.addPropertyChangeListener(this);
//        pack();
//    }
//    public void clearAndHide() {
//        textField.setText(null);
//        setVisible(false);
//    }
//
//    public void actionPerformed(ActionEvent e) {
//        optionPane.setValue("Enter");
//    }
//    public void propertyChange(PropertyChangeEvent e) {
//        String prop = e.getPropertyName();
//        if (isVisible() &&
//                e.getSource() == optionPane &&
//                JOptionPane.VALUE_PROPERTY.equals(prop) ||
//                JOptionPane.INPUT_VALUE_PROPERTY.equals(prop)){
//            Object value = optionPane.getValue();
//            if (value == JOptionPane.UNINITIALIZED_VALUE) {
//                return;
//            }
//            optionPane.setValue(JOptionPane.UNINITIALIZED_VALUE);
//            if("Enter".equals(value)) {
//                typedText = textField.getText();
//                String ucText = typedText.toUpperCase();
//                if (magicWord.equals(ucText)) {
//                    clearAndHide();
//                } else {
//                    textField.selectAll();
//                    JOptionPane.showMessageDialog(
//                            SwingDialog.this,
//                            "Sorry, \"" + typedText + "\" "
//                                    + "isn't a valid response.\n"
//                                    + "Please enter "
//                                    + magicWord + ".",
//                            "Try again",
//                            JOptionPane.ERROR_MESSAGE
//                    );
//                    typedText = null;
//                    textField.requestFocusInWindow();
//                }
//            } else {
//                typedText = null;
//                clearAndHide();
//            }
//        }
//    }
//
//}