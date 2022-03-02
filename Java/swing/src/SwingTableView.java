//import javax.swing.*;
//import javax.swing.table.DefaultTableModel;
//import java.awt.*;
//import java.awt.event.ActionEvent;
//import java.awt.event.ActionListener;
//import java.awt.event.KeyEvent;
//
//public class SwingTableView extends JFrame implements ActionListener {
//    JTable table;
//    public SwingTableView(DefaultTableModel model) {
//        Font font = new Font("Serif", Font.PLAIN, 24);
//
//        setTitle("TableView");
//
//        UIManager.put("Table.font", font);
//        table = new JTable();
//        table.setModel(model);
//        table.setRowHeight(24);
//        table.getTableHeader().setFont(font);
//        table.setPreferredScrollableViewportSize(new Dimension(800, 500));
//
//        JScrollPane scrollPane = new JScrollPane(table);
//        final JButton button = new JButton("Info");
//        button.setMnemonic(KeyEvent.VK_I);
//        button.setAlignmentX(RIGHT_ALIGNMENT);
//        button.setFont(font);
//        button.addActionListener(this);
//        button.setPreferredSize(new Dimension(800, 50));
//
//        JPanel panel = new JPanel();
//        panel.add(button);
//        getContentPane().setLayout(new BorderLayout());//(getContentPane(), BoxLayout.Y_AXIS));
//        add(scrollPane, BorderLayout.NORTH);
//        add(panel, BorderLayout.SOUTH);
//    }
//
//    public void actionPerformed(ActionEvent e) {
//        if(0 <= table.getSelectedRow()) {
//            int numCols = table.getColumnCount();
//            System.out.print(table.getSelectedRow() + "\t\t");
//            for (int i = 0; i < numCols; ++i) {
//                System.out.print(table.getModel().getValueAt(table.getSelectedRow(), i) + "\t\t");
//            }
//            System.out.println();
//        }
//    }
//}
