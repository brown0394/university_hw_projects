package com.fm.client.view;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fm.client.model.SearchPlayerModel;
import com.fm.search.SearchCondition;
import com.fm.search.SearchField;
import com.fm.server.model.PlayerRepository;
import com.fm.server.model.PlayerSearchPredicateFactory;
import com.fm.unit.Player;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
import java.util.List;
import java.util.Optional;

public class SearchPlayer {
    private static final String baseURL = "http://localhost:9000";

    private SearchPlayerModel model;

    public SearchPlayer(SearchPlayerModel model) {
        this.model = model;
    }

    public void searchPlayer(List<SearchCondition> condition) {
        String path = "/players?";
        StringBuilder qs = new StringBuilder();
        ObjectMapper objectMapper = new ObjectMapper();

        for(int i = 0; i < condition.size(); ++i) {
            if (i > 0) qs.append("&");
            qs.append(condition.get(i).getField() + "=" + condition.get(i).getCondition());
        }
        HttpClient client = HttpClient.newBuilder()
                .version(HttpClient.Version.HTTP_1_1)
                .followRedirects(HttpClient.Redirect.NORMAL)
                .build();

        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(baseURL + path + qs))
                .timeout(Duration.ofMinutes(1))
                .header("Content-Type", "application/json")
                .GET()
                .build();

        Optional<List<Player>> players = Optional.empty();
        try {
            HttpResponse<String> response =
                    client.send(request, HttpResponse.BodyHandlers.ofString());
            if (response.statusCode() == 200)
                players =
                        Optional.ofNullable(objectMapper.readValue(response.body(),
                                objectMapper.getTypeFactory().constructCollectionType(List.class, Player.class)));
        } catch (IOException ex) {
            System.err.println(ex);
        } catch (InterruptedException ex) {
            System.err.println(ex);
        }

        Object[][] newData = null;
        if (players.isPresent()) {
            newData = PlayerRepository.toArray(players.get());
        }
        model.setDataVector(newData, SearchPlayerModel.TABLE_HEADER);
    }
}
