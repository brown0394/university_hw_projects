package com.fm.client;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fm.client.model.SearchPlayerModel;
import com.fm.client.view.SearchPlayer;
import com.fm.client.view.SearchPlayerView;
import com.fm.search.SearchField;
import com.fm.unit.Player;

import javax.swing.*;
import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
import java.util.*;

public class PlayerClient {

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
        SearchPlayer controller = new SearchPlayer(model);
        //SearchPlayerController controller = new SearchPlayerController(model);
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

