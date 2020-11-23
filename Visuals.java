package AIvisuals;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;

public class Visuals extends Application {
    final int WINDOW_SIZE = 50;
    String path1 = "/home/herlock/Desktop/Sem5Projects/AI/HillClimbing.csv";
    String path3 = "/home/herlock/Desktop/Sem5Projects/AI/SimulatedAnnealing.csv";
    String path2 = "/home/herlock/Desktop/Sem5Projects/AI/HillClimbingWithRandomRestart.csv";
//    String path4 = "/home/herlock/Desktop/Sem5Projects/AI/MinConflictHeuristics.csv";



    private ScheduledExecutorService scheduledExecutorService;

    public static void main(String[] args) { launch(args); }

    @Override
    public void start(Stage primaryStage) throws Exception {
        primaryStage.setTitle("Realtime chart: Solving N-Queens");

        // defining the axes
        final NumberAxis xAxis = new NumberAxis(); // we are gonna plot against time
        final NumberAxis yAxis = new NumberAxis();
        xAxis.setLabel("N Queen");
        xAxis.setAnimated(true); // axis animations are removed
        yAxis.setLabel("Time in seconds");
        yAxis.setAnimated(true); // axis animations are removed

        // creating the line chart with two axis created above
        final LineChart<Number, Number> lineChart = new LineChart<>(xAxis, yAxis);
//        lineChart.setTitle("Runtime of Simulated Annealing for given N");
        lineChart.setTitle("Runtime of Hill Climbing for given N");
        lineChart.setAnimated(false); // disable animations

        // defining a series to display data
        XYChart.Series<Number, Number> series1 = new XYChart.Series<>();
//        series1.setName("Simulated Annealing");
        series1.setName("HillClimbing Annealing");





        // add series to chart
        lineChart.getData().addAll(series1);


        // setup scene
        Scene scene = new Scene(lineChart, 800, 600);
        primaryStage.setScene(scene);

        // show the stage
        primaryStage.show();



//         setup a scheduled executor to periodically put data into the chart
        scheduledExecutorService = Executors.newSingleThreadScheduledExecutor();


        scheduledExecutorService.scheduleAtFixedRate(() -> {

            // Update the chart
            Platform.runLater(() -> {
                try {
                    BufferedReader csvReader = new BufferedReader(new FileReader(path1));
//                    BufferedReader csvReader = new BufferedReader(new FileReader(path1));

                    int unsolv = 0;
                    String row;
                    while((row = csvReader.readLine()) != null){
                        String [] data = row.split(" ");
                        series1.getData().add(new XYChart.Data<Number, Number>(Integer.parseInt(data[0]), Double.parseDouble(data[1])));
                    }
                } catch (FileNotFoundException e) {
                    System.out.println("File Not Found\n");
                    e.printStackTrace();
                } catch (IOException e){
                    System.out.println("Exception in readline\n");
                    e.printStackTrace();
                }
                if (series1.getData().size() > WINDOW_SIZE)
                    series1.getData().remove(0);
            });
        }, 0, 1, TimeUnit.SECONDS);
    }

    @Override
    public void stop() throws Exception {

        super.stop();
        scheduledExecutorService.shutdownNow();
    }
}
