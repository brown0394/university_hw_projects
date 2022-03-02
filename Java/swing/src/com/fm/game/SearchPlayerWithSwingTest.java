package com.fm.game;

import com.fm.controller.SearchPlayerController;
import com.fm.model.SearchPlayerModel;
import com.fm.view.SearchPlayerView;

import javax.swing.*;

public class SearchPlayerWithSwingTest extends JFrame {
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
        // Create table model
        SearchPlayerModel model = new SearchPlayerModel();
        // Create controller
        SearchPlayerController controller = new SearchPlayerController(model);
        // Create view
        SearchPlayerView view = new SearchPlayerView(controller, model);
        // Make the window appear
        view.setTitle("FM - Find a Player");
        view.setSize(800, 800);
        view.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        view.pack();
        view.setVisible(true);
    }
}