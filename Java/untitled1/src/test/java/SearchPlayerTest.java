import com.fm.controller.SearchPlayerController;
import com.fm.model.SearchPlayerModel;
import com.fm.view.SearchPlayerView;
import org.assertj.swing.edt.GuiActionRunner;
import org.assertj.swing.fixture.FrameFixture;
import org.assertj.swing.junit.testcase.AssertJSwingJUnitTestCase;
import org.junit.Test;

import javax.swing.*;

public class SearchPlayerTest  extends AssertJSwingJUnitTestCase {
    private FrameFixture window;

    @Override
    protected void onSetUp() throws Exception {
        SearchPlayerView frame = GuiActionRunner.execute(() -> {
            // Create table model
            SearchPlayerModel model = new SearchPlayerModel();
            // Create controller
            SearchPlayerController controller = new SearchPlayerController(model);
            // Create view
            JTable table = new JTable();
            table.setName("foundPlayer");
            table.setModel(model);
            return new SearchPlayerView(controller, table);
        });
        window = new FrameFixture(robot(), frame);
        window.show();
    }

    @Test
    public void searchForPlayersWithNameOfMessi() {
        window.textBox("name").enterText("Messi");
        robot().settings().delayBetweenEvents(1000);
        window.button("Search").click();
        window.table("foundPlayer").requireRowCount(2);
    }

    @Test
    public void searchForPlayersBelongingToBarcelona() {
        window.textBox("club").enterText("Barcelona");
        robot().settings().delayBetweenEvents(1000);
        window.button("Search").click();
        window.table("foundPlayer").requireRowCount(33);
    }

    @Test
    public void searchForLeftWingerPlayersOfKorea() {
        window.textBox("nationality").enterText("Korea");
        window.textBox("position").enterText("LW");
        robot().settings().delayBetweenEvents(1000);
        window.button("Search").click();
        window.table("foundPlayer").requireRowCount(28);
    }

    @Test
    public void searchForTottenhamPlayersNamedSon() {
        window.textBox("name").enterText("Son");
        window.textBox("club").enterText("Tottenham");
        robot().settings().delayBetweenEvents(1000);
        window.button("Search").click();
        window.table("foundPlayer").requireRowCount(1);
    }
}