package com.fm.server;

import com.fm.server.model.PlayerRepository;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.util.concurrent.Executor;
import java.util.concurrent.Executors;

public class PlayerServer {
    private static final String HOSTNAME = "localhost";
    private static final int PORT = 9000;
    private static final int BACKLOG = 1;

    static {
        PlayerRepository.getInstance().load();
    }

    public static void main(final String... args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(HOSTNAME, PORT), BACKLOG);
        System.out.println(server.toString());
        server.createContext("/players", new PlayerHandler());
        server.setExecutor(Executors.newCachedThreadPool());
//        server.createContext("/quit", new HttpHandler() {
//            @Override
//            public void handle(HttpExchange exchange) throws IOException {
//                System.exit(0);
//            }
//        });
        server.start();
    }
}
