/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.lab.mymazegen;

import pl.polsl.lab.krzysztof.pieczynski.maze.controller.MazeController;
import pl.polsl.krzsztof.pieczynski.maze.model.MazeModel;
import pl.polsl.krzsztof.pieczynski.maze.model.User;
import pl.polsl.krzysztof.pieczynski.maze.view.MazeView;

/**
 * Main class of the program First and only command line argument: Name of the
 * user
 *
 * @author Krzysiek
 */
public class MainProgram {

    public static void main(String[] args) {

        //args[0] -> name of current user
        int widthInTiles = 120;
        int heightInTiles = 50;
        int tileSize = 10;
        int mazeOffsetX = 250;
        int mazeOffsetY = 250;
        int frameSizeX = 1500;
        int frameSizeY = 800;
        User programUser;

        if (args.length == 1) {
            programUser = new User(args[0]);
        } else {
            programUser = new User("default");

        }

        MazeView view = new MazeView(tileSize, frameSizeX, frameSizeY, mazeOffsetX, mazeOffsetY);

        MazeModel model = new MazeModel(widthInTiles, heightInTiles, programUser);

        MazeController controll = new MazeController(view, model);
        controll.start();

    }
}
