import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class DatabaseTest {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                try {
                    createAndShowGUI();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    public static void createAndShowGUI() throws Exception {

        JFrame view = new JFrame();
        JScrollPane scrollPane = setTable();
        JPanel buttonPanel = setButtons();
        JPanel inputPanel = setInputField();


        view.setLayout(new BorderLayout());
        view.add(inputPanel, BorderLayout.NORTH);
        view.add(buttonPanel, BorderLayout.CENTER);
        view.add(scrollPane, BorderLayout.SOUTH);
        view.setTitle("FM - Find a Player");
        view.setSize(800, 800);
        view.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        view.pack();
        view.setVisible(true);
    }

    static JTextField idtextField;
    static JTextField clubtextField;
    static PlayerRepository repository = new PlayerRepository();

    private static JPanel setInputField() {
        final int columns = 80;
        idtextField = new JTextField(columns);
        clubtextField = new JTextField(columns);
        JLabel idlabel = new JLabel("ID");
        JLabel clublabel = new JLabel("CLUB");
        JPanel idpanel = new JPanel();
        idpanel.setLayout(new FlowLayout(FlowLayout.LEFT, 65, 2));
        idpanel.add(idlabel);
        idpanel.add(idtextField);

        JPanel clubpanel = new JPanel();
        clubpanel.setLayout(new FlowLayout(FlowLayout.LEFT, 54, 2));
        clubpanel.add(clublabel);
        clubpanel.add(clubtextField);

        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.add(idpanel);
        panel.add(clubpanel);
        return panel;
    }

    private static JPanel setButtons() {
        JButton buttonSearch = new JButton("Search");
        JButton buttonCreate = new JButton("Create");
        JButton buttonDelete = new JButton("Delete");
        Dimension dimension = new Dimension(264, 25);
        buttonSearch.setPreferredSize(dimension);
        buttonDelete.setPreferredSize(dimension);
        buttonCreate.setPreferredSize(dimension);
        SwingDialog dialog = new SwingDialog();
        buttonSearch.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (idtextField.getText().equalsIgnoreCase("")) {
                    if (!clubtextField.getText().equalsIgnoreCase("")) {
                        Optional<List<Player>> players = repository.findClub(clubtextField.getText());
                        players.ifPresent(playerList -> model.setDataVector(toArray(playerList), TABLE_HEADER));
                    }
                }
                else {
                    if (clubtextField.getText().equalsIgnoreCase("")) {

                        Optional<Player> player = repository.findById(Integer.parseInt(idtextField.getText()));
                        if (player.isPresent()) {
                            List<Player> p = new ArrayList<>();
                            p.add(player.get());
                            model.setDataVector(toArray(p), TABLE_HEADER);
                        }
                        else {
                            model.setDataVector(null, TABLE_HEADER);
                        }
                    }
                    else {
                        JOptionPane.showMessageDialog(
                                dialog,
                                "One of the Input Field should be EMPTY",
                                "Cant take two inputs",
                                JOptionPane.ERROR_MESSAGE
                        );
                    }
                }

            }
        });

        buttonCreate.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dialog.setVisible(true);
            }
        });

        buttonDelete.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String input = idtextField.getText();
                if (!input.equalsIgnoreCase("")) {
                    boolean valid = true;
                    for (int i = 0; i < input.length(); ++i) {
                        if (!Character.isDigit(input.charAt(i))) {
                            valid = false;
                            break;
                        }
                    }
                    if (valid) {
                        repository.deleteById(Integer.parseInt(idtextField.getText()));
                        JOptionPane.showMessageDialog(
                                dialog,
                                "Deleted " + idtextField.getText(),
                                "Done",
                                JOptionPane.PLAIN_MESSAGE
                        );
                    }
                    else {
                        JOptionPane.showMessageDialog(
                                dialog,
                                "ID Input Should be Digits",
                                "Error",
                                JOptionPane.ERROR_MESSAGE
                        );
                    }
                }
            }
        });

        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout());
        buttonPanel.add(Box.createHorizontalStrut(71));
        buttonPanel.add(buttonCreate);
        buttonPanel.add(buttonDelete);
        buttonPanel.add(buttonSearch);
        return buttonPanel;
    }


    static DefaultTableModel model;
    public static final Object[] TABLE_HEADER = { "ID", "Player Name",
            "Height", "Nationality", "Club", "Overall", "positions" };
    private static JScrollPane setTable() {
        model = new DefaultTableModel(toArray(repository.findAll()), TABLE_HEADER);
        // Font font = new Font("Serif", Font.PLAIN, 15);
        JTable table = new JTable();
        //  UIManager.put("Table.font", font);
        table.setModel(model);
        table.setRowHeight(24);
        // table.getTableHeader().setFont(font);
        table.setPreferredScrollableViewportSize(new Dimension(800, 500));
        return new JScrollPane(table);
    }

    private static class SwingDialog extends JDialog implements ActionListener, PropertyChangeListener {
        private JOptionPane optionPane;
        private JTextField textFields[] = new JTextField[7];
        final int SOFIFA = 0;
        final int NAME = 1;
        final int HEIGHT = 2;
        final int NATIONALITY = 3;
        final int CLUB = 4;
        final int OVERALL = 5;
        final int POSITION = 6;


        protected SwingDialog() {
            setTitle("Create");
            for (int i = 0; i < 7; ++i) {
                textFields[i] = new JTextField(20);
            }
            String msg = "From top insert SOFIFA_ID, Name, Height, Nationality, Club, Overall, Positions";
            Object[] array = {msg, textFields[SOFIFA], textFields[NAME], textFields[HEIGHT],
            textFields[NATIONALITY], textFields[CLUB], textFields[OVERALL], textFields[POSITION]};
            Object[] options = {"Create", "Cancel"};

            optionPane = new JOptionPane(array, JOptionPane.PLAIN_MESSAGE,
                    JOptionPane.YES_NO_OPTION, null, options, options[0]);
            setContentPane(optionPane);
            setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
            addWindowListener(new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e) {
                    optionPane.setValue(JOptionPane.CLOSED_OPTION);
                }
            });
            addComponentListener(new ComponentAdapter() {
                @Override
                public void componentShown(ComponentEvent e) {
                    textFields[0].requestFocusInWindow();
                }
            });
            for (int i = 0; i < 7; ++i) {
                textFields[i].addActionListener(this);
            }
            optionPane.addPropertyChangeListener(this);
            pack();
        }
        public void clearAndHide() {
            for (JTextField t : textFields) {
                t.setText(null);
            }
            //textField.setText(null);
            setVisible(false);
        }

        public void actionPerformed(ActionEvent e) {
            optionPane.setValue("Create");
        }
        public void propertyChange(PropertyChangeEvent e) {
            String prop = e.getPropertyName();
            if (isVisible() &&
                    e.getSource() == optionPane &&
                    JOptionPane.VALUE_PROPERTY.equals(prop) ||
                    JOptionPane.INPUT_VALUE_PROPERTY.equals(prop)){
                Object value = optionPane.getValue();
                if (value == JOptionPane.UNINITIALIZED_VALUE) {
                    return;
                }
                optionPane.setValue(JOptionPane.UNINITIALIZED_VALUE);
                if("Create".equals(value)) {
                    boolean allfilled = true;
                    for (JTextField t : textFields) {
                        if (t.getText().equalsIgnoreCase("")) {
                            allfilled = false;
                            break;
                        }
                    }
                    if (allfilled) {
                        //create
                        List<String> position = Arrays.stream(textFields[POSITION].getText().split(", ")).toList();
                        repository.save(new Player(Integer.parseInt(textFields[SOFIFA].getText()), textFields[NAME].getText(),
                                Integer.parseInt(textFields[HEIGHT].getText()), textFields[NATIONALITY].getText(),
                                textFields[CLUB].getText(), Integer.parseInt(textFields[OVERALL].getText()), position));
                        JOptionPane.showMessageDialog(
                                SwingDialog.this,
                                "Created Player ",
                                "Created",
                                JOptionPane.PLAIN_MESSAGE
                        );
                        clearAndHide();
                    } else {
                        JOptionPane.showMessageDialog(
                                SwingDialog.this,
                                "You should fill all the fields",
                                "Empty Fields",
                                JOptionPane.ERROR_MESSAGE
                        );
                        //textField.requestFocusInWindow();
                    }
                } else {
                    clearAndHide();
                }
            }
        }

    }

    public static Object[][] toArray(List<Player> players){
        Object[][] result = new Object[players.size()][Player.class.getDeclaredFields().length];
        for(int i=0; i < players.size(); i++)
            result[i] = players.get(i).toArray();
        return result;
    }
}
