import com.fm.game.SearchCondition;
import com.fm.repository.FileRepository;
import com.fm.repository.IRepository;
import com.fm.repository.PlayerFactory;
import com.fm.repository.PlayerSearchPredicateFactory;
import com.fm.unit.Player;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Scanner;
import java.util.function.Predicate;

public class StreamTest {
    private static IRepository repository = FileRepository.getInstance();
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        List<SearchCondition> searchConditions = new ArrayList<>();
        boolean success = false;
        while (scanner.hasNext()) {
            String option = scanner.nextLine();
            String[] params = option.split(":");
            switch (params[0]) {
                case "club":
                case "nationality":
                case "name":
                case "position":
                    success = searchConditions.add(new SearchCondition(params[0], params[1]));
                    break;
                case "search":
                    success = searchPlayer(searchConditions);
                    break;
                case "create":
                    success = createAndSavePlayer(params[1]);
                    break;
                case "delete":
                    success = deletePlayer(params[1]);
                    break;
                case "count":
                    getPlayerCount();
                    success = true;
                    break;
                case "quit":
                default:
                    success = false;
            }
            if (!success) break;
        }
        scanner.close();
    }

    private static int getPlayerCount() {
        int result = repository.count();
        System.out.printf("Total Players: %d\n", result);
        return result;
    }

    private static boolean searchPlayer(List<SearchCondition> searchConditions) {
        List<Predicate<Player>> conditions = PlayerSearchPredicateFactory.makeConditions(searchConditions);
        IRepository repository = FileRepository.getInstance();
        List<Player> result = repository.findByConditions(conditions);
        System.out.printf("%d - %s\n", result.size(), result);
        searchConditions.clear();
        return true;
    }

    private static boolean createAndSavePlayer(String fields) {
        //L. Messi,170,Argentina,FC Barcelona,94,"RW, CF, ST"
        Player newPlayer = PlayerFactory.createPlayersWithoutID(fields.split(","));
        repository.save(newPlayer);
        System.out.printf("%s(%d) is registered!\n", newPlayer.getName(), newPlayer.getId());
        return true;
    }

    private static boolean deletePlayer(String id) {
        IRepository repository = FileRepository.getInstance();
        Optional<Player> foundPlayer = repository.findById(Integer.parseInt(id));
        if (foundPlayer.isPresent()) {
            repository.delete(foundPlayer.get());
            System.out.printf("%s(%d) is deregistered!\n", foundPlayer.get().getName(), foundPlayer.get().getId());
            return true;
        }
        return false;
    }
}