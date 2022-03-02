package com.fm.client;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fm.search.SearchField;
import com.fm.unit.Player;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.InetSocketAddress;
import java.net.ProxySelector;
import java.net.URI;
import java.net.URLEncoder;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;
import java.util.*;

public class PlayerClient {
    private static final String baseURL = "http://localhost:9000";
    private static final HttpClient client = HttpClient.newBuilder()
            .version(HttpClient.Version.HTTP_1_1)
            .followRedirects(HttpClient.Redirect.NORMAL)
            .build();

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        List<String> str = Arrays.stream(input.split(" ")).toList();
        int count = 0;

        List<SearchField> sfield = new ArrayList<>();
        List<String> condition = new ArrayList<>();

        for (String s : str) {
            if ((count % 2) == 0) {
                switch (s.toLowerCase()) {
                    case "name": {
                        sfield.add(SearchField.NAME);
                        break;
                    }
                    case "club": {
                        sfield.add(SearchField.CLUB);
                        break;
                    }
                    case "position": {
                        sfield.add(SearchField.POSITION);
                        break;
                    }
                    case "nationality": {
                        sfield.add(SearchField.NATIONALITY);
                        break;
                    }
                }
            } else {
                condition.add(s);
            }
            ++count;
        }

        Optional<List<Player>> result = searchPlayer(sfield, condition);
        result.ifPresent(System.out::println);

        scanner.close();
    }

    public static Optional<List<Player>> searchPlayer(List<SearchField> field, List<String> condition) {
        String path = "/players?";
        StringBuilder qs = new StringBuilder();
        ObjectMapper objectMapper = new ObjectMapper();

        for (int i = 0; i < field.size(); ++i) {
            if (i > 0) qs.append("&");
            qs.append(String.valueOf(field.get(i)) + "=" + condition.get(i));
        }

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
        return players;
    }
}

