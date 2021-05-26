/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.lab.krzysztof.pieczynski.maze.controller;

import pl.polsl.krzsztof.pieczynski.maze.model.Cell;
import pl.polsl.krzsztof.pieczynski.maze.model.MazeModel;
import pl.polsl.krzysztof.pieczynski.maze.view.MazeView;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
import java.util.logging.Logger;
import pl.polsl.krzsztof.pieczynski.maze.model.MazeModel.Location;
import pl.polsl.lab.krzysztof.pieczynski.maze.exception.PositionException;

/**
 * Manages view and model
 *
 * @author Krzysiek ////
 */
public class MazeController {

    private MazeView view;
    private MazeModel model;

    /**
     * Construct controller and adds listeners for buttons
     *
     * @param theView View of the maze
     * @param theModel Model of the maze
     */
    public MazeController(MazeView theView, MazeModel theModel) {
        this.view = theView;
        this.model = theModel;

        initListeners();
    }

    /**
     * Generates first frame
     */
    public void start() {
        this.view.setVisible(true);
        //   model.generateMaze();

    }

    /**
     * Adds all listeners to buttons
     */
    private void initListeners() {
        this.view.addGenerateMazeListener(new GenerateMazeBut());
        this.view.addStartPosButtnoList(new listenStartPos());
        this.view.addEndPosButtnoList(new listenEndPos());
        this.view.addSolvelist(new listensolve());
        this.view.addChengeNameListener(new listenerUserName());
        this.view.addAlgorithmNameBoxListener(new listenerAlgorithmName());
        this.view.addClearMazeButtonListener(new listenerClearMaze());
        this.view.addDeleteRandomWallsListener(new listenRandomWalls());
    }

    /**
     * Repaints maze without colored cells
     */
    public void clearMaze() {
        this.view.clearScreen();
        printMaze();
    }

    /**
     * Prints maze on screen
     */
    public void printMaze() {
        int cell_size = view.getTILE_SIZE();
        for (int i = 0; i < model.maze.size(); i++) {
            Cell current = this.model.maze.get(i);

            this.view.renderCell(
                    current.getX() * cell_size, current.getY() * cell_size,
                    current.isUp(), current.isRight(), current.isDown(), current.isLeft());
        }
        int x = model.getHeight();
        view.renderIndexes(model.getWidth(), model.getHeight());
    }

    /**
     * Prints path, dt is the time between each cell being colored
     *
     * @param path List of int to print
     */
    public void printPath(List<Integer> path) {
        if (path.isEmpty()) {
            return;
        }

        path.remove(0);
        int dt = 2000 / path.size();
        if (dt < 5) {
            dt = 5;
        }
        for (int i : path) {
            view.colorCell(i % model.getWidth(), i / model.getWidth(), 0);
            try {
                TimeUnit.MILLISECONDS.sleep(dt);
            } catch (InterruptedException ex) {
                Logger.getLogger(MazeController.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    /**
     * Listener for ereasing random walls
     */
    class listenRandomWalls implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent arg0) {
            model.setAllCellsUnvisited();
            model.eraseRandomWalls();
            view.clearScreen();
            printMaze();
        }

    }

    /**
     * Listener for clearing maze
     */

    class listenerClearMaze implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent arg0) {
            clearMaze();
            model.setAllCellsUnvisited();
        }

    }

    /**
     * Provides listener for algorithm names comboBox
     */
    class listenerAlgorithmName implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent arg0) {
            model.setAllCellsUnvisited();
            view.clearScreen();
            printMaze();

        }

    }

    /**
     * Provides listener for changing username
     */
    class listenerUserName implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent arg0) {
            model.changeUserName(view.getName());
        }

    }

    /**
     * Implements listeren for Solve button. Here all solving algorithms are
     * executed
     */
    class listensolve implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent arg0) {
            List<Integer> path = new ArrayList();

            int start_x = 0, start_y = 0, end_x = 0, end_y = 0;
            try {
                start_x = view.getStartPosX();
                start_y = view.getStartPosY();
                end_x = view.getEndPosX();
                end_y = view.getEndPosY();
            } catch (NumberFormatException ex) {
                view.displayErrorMessage("Enter start and end position");
            }

            try {
                model.checkPositionBounds(start_x, start_y);
                model.checkPositionBounds(end_x, end_y);
            } catch (PositionException ex) {
                view.displayErrorMessage(ex.getMessage());
                return;
            }

            model.setAllCellsUnvisited();
            long start = System.nanoTime();

            String algName = view.getAlgorihtmName();
            switch (algName) {
                case "BFS-URDL":
                    model.solveWithGivenAlgorithm(MazeModel.Algorithm.BFSurdl, start_x, start_y, end_x, end_y, path);
                    break;
                case "BFS-DRLU":
                    model.solveWithGivenAlgorithm(MazeModel.Algorithm.BFSdrlu, start_x, start_y, end_x, end_y, path);
                    break;
                case "ASTAR":
                    model.solveWithGivenAlgorithm(MazeModel.Algorithm.Astar, start_x, start_y, end_x, end_y, path);
                    break;
            }
            long finish = System.nanoTime();
            long timeElapsed = finish - start;
            model.user.addAlgorithmData(algName, timeElapsed, path.size());

            view.addTableRow(algName, timeElapsed, path.size());

            printPath(path);

        }

    }

    /**
     * Implements listeren for GenerateMaze button. Clears old maze, generates
     * new one and then prints it
     */
    class GenerateMazeBut implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent arg0) {
            view.clearScreen();
            model.resetMaze();
            model.generateMaze();
            model.setAllCellsUnvisited();
            printMaze();
        }
    }

    /**
     * Implements listeren for StartPos button. Gets starting point from
     * TExtField
     */
    class listenStartPos implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent arg0) {
            int pos_x = 0;
            int pos_y = 0;
            try {
                pos_x = view.getStartPosX();
                pos_y = view.getStartPosY();
            } catch (NumberFormatException ex) {
                view.displayErrorMessage("Enter start and end position");
            }

            try {
                model.checkPositionBounds(pos_x, pos_y);
            } catch (PositionException ex) {
                view.displayErrorMessage(ex.getMessage());
            }

            view.colorCell(pos_x, pos_y, 1);
        }
    }

    /**
     * Implements listeren for EndPos button. Gets ending point from TextField
     */
    class listenEndPos implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent arg0) {
            int pos_x = 0;
            int pos_y = 0;
            try {
                pos_x = view.getEndPosX();
                pos_y = view.getEndPosY();
            } catch (NumberFormatException ex) {
                view.displayErrorMessage("Enter start and end position");
            }

            try {
                model.checkPositionBounds(pos_x, pos_y);
            } catch (PositionException ex) {
                view.displayErrorMessage(ex.getMessage());
            }

            view.colorCell(pos_x, pos_y, 2);
        }

    }

}
