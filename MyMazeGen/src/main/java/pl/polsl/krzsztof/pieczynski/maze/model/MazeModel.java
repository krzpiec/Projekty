/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.krzsztof.pieczynski.maze.model;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Deque;
import java.util.List;
import java.util.Random;
import javax.swing.JFrame;
import pl.polsl.lab.krzysztof.pieczynski.maze.exception.PositionException;

/**
 * This class represents data structure of the maze. Manages data,logic and
 * rules. Maze is represented as 1d array of cells Path between every two points
 * in this maze exists Maze dont have entry and leave doors by default, they
 * have to be defined as start/end point
 *
 * @author Krzysiek
 */
public class MazeModel extends JFrame {

    /**
     * Represents possible location of cells
     */
    public enum Location {
        None,
        Up,
        Right,
        Down,
        Left
    }

    public enum Algorithm {
        BFSurdl,
        BFSdrlu,
        Astar,
        Dijkstra
    }

    /**
     * Stores width of the maze as number of tiles
     */
    private int WIDTH;
    /**
     * Stores height of the maze as number of tiles
     */
    private int HEIGHT;

    /**
     * Array of Cells, represents maze
     */
    public List<Cell> maze;

    /**
     * Holds current user and alg data inside
     */
    public User user;

    /**
     * Contructs and initializes Model
     *
     * @param W width of the maze
     * @param H height of the maze
     * @param user Current user
     */
    public MazeModel(int W, int H, User user) {
        this.WIDTH = W;
        this.HEIGHT = H;
        this.user = user;

        initCells();

    }

    public int getHeight() {
        return this.HEIGHT;
    }

    public int getWidth() {
        return this.WIDTH;
    }

    /**
     * Changes name and surname of the user
     *
     * @param name user name
     */
    public void changeUserName(String name) {
        user.setName(name);

    }

    /**
     * Initializes maze with cell with all walls active
     */
    private void initCells()//all cells with all walls active
    {
        this.maze = new ArrayList<>();
        int idCount = 0;

        for (int j = 0; j < HEIGHT; j++) {
            for (int i = 0; i < WIDTH; i++) {
                this.maze.add(new Cell(idCount, i, j, true, true, true, true));
                idCount++;
            }
        }
    }

    /**
     * Convertts 2d array position to 1d array position
     *
     * @param i x coordinate
     * @param j y coordinate
     * @return returns -1 if position is incorrect otherwise returns 1d array
     * position
     */
    private int oneDimensionalArrIndex(int i, int j) {
        if (i < 0 || i > WIDTH - 1 || j < 0 || j > HEIGHT - 1) {
            return -1;
        }
        return i + j * WIDTH;
    }

    /**
     * Creates array of possible cells to go(unvisited neighbour) then randomly
     * chooses one of them and returns choosen cell Used by BFS algorithm
     *
     * @param currentX x coordinate
     * @param currentY y coordinate
     * @return Randomly choosen unvisited neighbour
     */
    private Cell checkNeighboursBFS(int currentX, int currentY) {
        List<Cell> possibleNeighbours = new ArrayList<>();

        //check top neighbour
        int topNeighbourIndex = oneDimensionalArrIndex(currentX, currentY - 1); // calculate 1d index
        {
            if (topNeighbourIndex != -1) //if index is correct 
            {
                if (!this.maze.get(topNeighbourIndex).isVisited()) // if not visited
                {
                    possibleNeighbours.add(this.maze.get(topNeighbourIndex)); // add to possible neighbours array
                }
            }
        }

        //check right 
        int rightNeighbourIndex = oneDimensionalArrIndex(currentX + 1, currentY);
        {
            if (rightNeighbourIndex != -1) {
                if (!this.maze.get(rightNeighbourIndex).isVisited()) {
                    possibleNeighbours.add(this.maze.get(rightNeighbourIndex));
                }

            }

        }

        //check bottom 
        int bottomNeighbourIndex = oneDimensionalArrIndex(currentX, currentY + 1);
        {
            if (bottomNeighbourIndex != -1) {
                if (!this.maze.get(bottomNeighbourIndex).isVisited()) {
                    possibleNeighbours.add(this.maze.get(bottomNeighbourIndex));
                }

            }

        }

        //check left
        int leftNeighbourIndex = oneDimensionalArrIndex(currentX - 1, currentY);
        {
            if (leftNeighbourIndex != -1) {
                if (!this.maze.get(leftNeighbourIndex).isVisited()) {
                    possibleNeighbours.add(this.maze.get(leftNeighbourIndex));
                }

            }

        }

        //randomize next cell from available
        Random rand = new Random();
        if (possibleNeighbours.size() == 0) {
            return null;
        } else {
            return possibleNeighbours.get(rand.nextInt(possibleNeighbours.size()));
        }
    }

    /**
     * Removes walls based on cell positions Modifies cell itself Possible cell
     * arrangment a b
     *
     * b a
     * a
     * b
     *
     * b
     * a
     *
     * @param a First cell
     * @param b Second cell
     */
    private void removeWalls(Cell a, Cell b) {
        int diffX = a.getX() - b.getX();
        if (diffX == 1) // b a
        {
            a.setLeft(false);
            b.setRight(false);
        } else if (diffX == -1) // a b
        {
            a.setRight(false);
            b.setLeft(false);
        }

        int diffY = a.getY() - b.getY();
        //b
        //a
        if (diffY == 1) {
            a.setUp(false);
            b.setDown(false);
        } //a
        //b
        else if (diffY == -1) {
            a.setDown(false);
            b.setUp(false);
        }
    }

    /**
     * Generates complete maze Implementation of Recursive backtracker algorithm
     *
     */
    public void generateMaze() {
        Deque<Cell> stack = new ArrayDeque<>();
        Cell current = this.maze.get(0); // get top left corner --> start point
        current.setVisited(true);

        while (current != null) {
            Cell next = checkNeighboursBFS(current.getX(), current.getY());
            if (next != null)//if there is a neighbour
            {
                stack.push(current); // add first element to the top 
                removeWalls(current, next);
                next.setVisited(true); // mark next as visited
                current = next;
            } else// no neighbours found
            {
                if (stack.size() != 0) // if stack not empty, 
                {
                    stack.pop(); //remove first item
                    current = stack.peek(); // make current new stack front (backtracker)
                } else {
                    break; //end loop
                }
            }
        }
    }

    /**
     * Resenting maze to its default state - every cell is unvisited and all
     * walls are active
     */
    public void resetMaze() {
        for (int i = 0; i < this.maze.size(); i++) {
            this.maze.get(i).resetWalls();
            this.maze.get(i).setVisited(false);
        }

    }

    /**
     * Sets all cells to unvisited
     */
    public void setAllCellsUnvisited() {
        for (int i = 0; i < this.maze.size(); i++) {
            this.maze.get(i).setVisited(false);
        }
    }

    /**
     * Runs algorithm with given name
     *
     * @param name Name of the algorithm
     * @param startX Starting position, x cooridinate
     * @param startY Starting position, y cooridinate
     * @param endX Ending position, x coordinate
     * @param endY Ending position, y coordinate
     * @param path List of cell indexes which build a path
     */
    public void solveWithGivenAlgorithm(Algorithm name, int startX, int startY, int endX, int endY, List<Integer> path) {
        switch (name) {
            case BFSurdl:
                BFSurdl(Location.None, startX, startY, endX, endY, path);
                break;
            case BFSdrlu:
                BFSdrlu(Location.None, startX, startY, endX, endY, path);
                break;
            case Astar:
                Astar(startX, startY, endX, endY, path);
                break;

        }

    }

    /**
     * Implementation of BFS search algorithm. Goes recursively through the maze
     * to find path from starting point to the end
     * Prefered directions DOWN - RIGHT - LEFT - UP
     *
     * @param prevCellLocation Indicates where previous cell was located.
     * @param startX x coordinate of start point
     * @param startY y coordinate of start point
     * @param endX x coordinate of end point
     * @param endY y coordinate of end point
     * @param path Array of cells which indicates solved path
     * @return Returns true if path was found
     */
    public boolean BFSdrlu(Location prevCellLocation, int startX, int startY, int endX, int endY, List<Integer> path) {

        if (startX == endX && startY == endY) // if we reached end
        {
            return true;
        }

        int current = oneDimensionalArrIndex(startX, startY);

        this.maze.get(current).setVisited(true);

        path.add(current); // add cell to solution

        int downNeighbourIndex = oneDimensionalArrIndex(startX, startY + 1);

        if (downNeighbourIndex != -1) {
            if (prevCellLocation != Location.Up) {
                if (!this.maze.get(current).isDown()) {
                    if (this.maze.get(downNeighbourIndex).isVisited() == false) {
                        if (BFSdrlu(Location.Down, startX, startY + 1, endX, endY, path) == true) {
                            return true;
                        }
                    }
                }

            }

        }

        int rightNeighbourIndex = oneDimensionalArrIndex(startX + 1, startY);
        if (rightNeighbourIndex != -1) {
            if (prevCellLocation != Location.Left) {
                if (!this.maze.get(current).isRight()) {
                    if (this.maze.get(rightNeighbourIndex).isVisited() == false) {
                        if (BFSdrlu(Location.Right, startX + 1, startY, endX, endY, path) == true) {
                            return true;
                        }
                    }
                }

            }

        }

        int leftNeighbourIndex = oneDimensionalArrIndex(startX - 1, startY);

        if (leftNeighbourIndex != -1) {
            if (prevCellLocation != Location.Right) {
                if (!this.maze.get(current).isLeft()) {
                    if (this.maze.get(leftNeighbourIndex).isVisited() == false) {
                        if (BFSdrlu(Location.Left, startX - 1, startY, endX, endY, path) == true) {
                            return true;
                        }
                    }
                }

            }

        }

        //can we go up?
        int topNeighbourIndex = oneDimensionalArrIndex(startX, startY - 1);//calculate top index
        if (topNeighbourIndex != -1)// if index is correct
        {
            if (prevCellLocation != Location.Down) // we dont want to go back
            {
                if (!this.maze.get(current).isUp()) // if there is no wall
                {
                    if (this.maze.get(topNeighbourIndex).isVisited() == false) {
                        if (BFSdrlu(Location.Up, startX, startY - 1, endX, endY, path) == true) //reccurency
                        {
                            return true;
                        }
                    }
                }

            }

        }

        path.remove(path.size() - 1);// if all of the above finished calls with false remove cell from solution
        return false;
    }

    /**
     * Implementation of BFS search algorithm. Goes recursively through the maze
     * to find path from starting point to the end
     * Preffered directions UP-RIGHT-DOWN-LEFT
     * 
     * @param prevCellLocation Indicates where previous cell was located.
     * @param startX x coordinate of start point
     * @param startY y coordinate of start point
     * @param endX x coordinate of end point
     * @param endY y coordinate of end point
     * @param path Array of cells which indicates solved path
     * @return Returns true if path was found
     */
    public boolean BFSurdl(Location prevCellLocation, int startX, int startY, int endX, int endY, List<Integer> path) {
        if (startX == endX && startY == endY) // if we reached end
        {
            return true;
        }

        int current = oneDimensionalArrIndex(startX, startY);

        this.maze.get(current).setVisited(true);

        path.add(current); // add cell to solution
        //can we go up?
        int topNeighbourIndex = oneDimensionalArrIndex(startX, startY - 1);//calculate top index
        if (topNeighbourIndex != -1)// if index is correct
        {
            if (prevCellLocation != Location.Down) // we dont want to go back
            {
                if (!this.maze.get(current).isUp()) // if there is no wall
                {
                    if (this.maze.get(topNeighbourIndex).isVisited() == false) {
                        if (BFSurdl(Location.Up, startX, startY - 1, endX, endY, path) == true) //reccurency
                        {
                            return true;
                        }
                    }
                }

            }

        }

        int rightNeighbourIndex = oneDimensionalArrIndex(startX + 1, startY);
        if (rightNeighbourIndex != -1) {
            if (prevCellLocation != Location.Left) {
                if (!this.maze.get(current).isRight()) {
                    if (this.maze.get(rightNeighbourIndex).isVisited() == false) {
                        if (BFSurdl(Location.Right, startX + 1, startY, endX, endY, path) == true) {
                            return true;
                        }
                    }
                }

            }

        }

        int downNeighbourIndex = oneDimensionalArrIndex(startX, startY + 1);

        if (downNeighbourIndex != -1) {
            if (prevCellLocation != Location.Up) {
                if (!this.maze.get(current).isDown()) {
                    if (this.maze.get(downNeighbourIndex).isVisited() == false) {
                        if (BFSurdl(Location.Down, startX, startY + 1, endX, endY, path) == true) {
                            return true;
                        }
                    }
                }

            }

        }

        int leftNeighbourIndex = oneDimensionalArrIndex(startX - 1, startY);

        if (leftNeighbourIndex != -1) {
            if (prevCellLocation != Location.Right) {
                if (!this.maze.get(current).isLeft()) {
                    if (this.maze.get(leftNeighbourIndex).isVisited() == false) {
                        if (BFSurdl(Location.Left, startX - 1, startY, endX, endY, path) == true) {
                            return true;
                        }
                    }
                }

            }

        }

        path.remove(path.size() - 1);// if all of the above finished calls with false remove cell from solution
        return false;
    }

    /**
     * Checks if array contains at least one 1
     *
     * @param arr Array to search in
     * @return
     */
    private boolean isMyArrayEmpty(int arr[]) {
        for (int i = 0; i < maze.size(); i++) {
            if (arr[i] == 1) {
                return false;
            }
        }
        return true;
    }

    /**
     * Gets all neighbours of 1d array index
     *
     * @param index Index of cell for which we need neighbours
     * @return
     */
    private List<Integer> getAllNeighbours(int index) {
        List<Integer> neighbours = new ArrayList<>();

        if (index - 1 >= 0 && !maze.get(index).isLeft()) // left neighb
        {
            neighbours.add(index - 1);
        }
        if ((index + 1) % WIDTH != 0 && !maze.get(index).isRight()) // right 
        {
            neighbours.add(index + 1);
        }
        if (index - WIDTH >= 0 && !maze.get(index).isUp()) // up
        {
            neighbours.add(index - WIDTH);
        }
        if (index + WIDTH < WIDTH * HEIGHT && !maze.get(index).isDown()) // down
        {
            neighbours.add(index + WIDTH);
        }

        return neighbours;
    }

    /**
     * Calucates heuristics for start cell
     *
     * @param start start cell
     * @param end end cell
     * @return
     */
    private int heuristic(int start, int end) {
        int dist = start - end;
        if (dist < 0) {
            dist = -dist;
        }

        int stepsX = dist / WIDTH;
        int stepsY = dist % WIDTH;

        int totalSteps = stepsX + stepsY;

        return totalSteps;
    }

    private List<Integer> reconstructPath(int cameFrom[], int current, List<Integer> path) {

        path.add(current);
        while (current != -2) {
            current = cameFrom[current];
            path.add(current);

        }
        return path;

    }

    /**
     * Implementation of Astar algorithm
     *
     * @param startX x coordinate of start point
     * @param startY y coordinate of start point
     * @param endX x coordinate of end point
     * @param endY y coordinate of end point
     * @param path Array of cells which indicates solved path
     * @return Returns true if path was found
     */
    public boolean Astar(int startX, int startY, int endX, int endY, List<Integer> path) {

        int gScore[] = new int[maze.size()];
        Arrays.fill(gScore, 50000);

        int cameFrom[] = new int[maze.size()];
        Arrays.fill(gScore, -1);

        int fScore[] = new int[maze.size()];
        Arrays.fill(fScore, 50000);
        int openSet[] = new int[maze.size()];
        Arrays.fill(openSet, 0);
        int closedSet[] = new int[maze.size()];
        Arrays.fill(closedSet, 0);

        int startIndex = oneDimensionalArrIndex(startX, startY);
        gScore[0] = 0;
        fScore[0] = 0;
        int endIndex = oneDimensionalArrIndex(endX, endY);
        openSet[startIndex] = 1;
        cameFrom[startIndex] = -2;
        while (!isMyArrayEmpty(openSet)) {

            int lowestfScore = 0;
            for (int i = 0; i < maze.size(); i++) {
                if (openSet[i] == 1) {
                    lowestfScore = i;
                    break;
                }
            }

            for (int i = 0; i < maze.size(); i++) {
                if (openSet[i] == 1) {
                    if (fScore[i] < fScore[lowestfScore]) {
                        lowestfScore = i;
                    }
                }

            }

            int current = lowestfScore;

            if (current == endIndex) {
                path = reconstructPath(cameFrom, current, path);
                path.remove(path.size() - 1);
                path.remove(path.size() - 1);
                return true;
            }
            closedSet[current] = 1;
            openSet[current] = 0;

            List<Integer> neighb = getAllNeighbours(current);
            for (int i : neighb) {
                if (closedSet[i] == 0) {

                    int tempG = gScore[current] + 1;
                    if (openSet[i] == 1) {
                        if (tempG < gScore[i]) {
                            gScore[i] = tempG;
                        }
                    } else {
                        gScore[i] = tempG;
                        openSet[i] = 1;
                    }

                    fScore[i] = gScore[i] + heuristic(i, endIndex);
                    cameFrom[i] = current;
                }

            }
        }
        return false;

    }

    private boolean checkIfBorderIndex(int index) {
        if (index < WIDTH) {
            return true;
        }
        if (index % WIDTH == 0) {
            return true;
        }
        if (index % WIDTH == WIDTH - 1) {
            return true;
        }
        if (index - (HEIGHT - 1) * WIDTH >= 0) {
            return true;
        }
        return false;
    }

    /**
     * Erases randomized walls from maze. Erased walls are 5% of all walls in
     * the maze
     */
    public void eraseRandomWalls() {
        int nOfRandomizedNumbers = (int) (maze.size() * 0.3);
        ArrayList<Integer> possibleIndexes = new ArrayList<Integer>(maze.size());
        for (int i = 0; i < maze.size(); i++) {
            if (!checkIfBorderIndex(i)) {
                possibleIndexes.add(i);
            }

        }

        Random rand = new Random();
        List<Integer> randomizedIndexes = new ArrayList<>();

        for (int i = 0; i < nOfRandomizedNumbers; i++) {
            int index = rand.nextInt(possibleIndexes.size());
            randomizedIndexes.add(possibleIndexes.get(index));
            possibleIndexes.remove(index);
        }

        for (int i : randomizedIndexes) {
            int randomNeighbour = rand.nextInt(4);// 0 1 2 3
            ereaseWallsNumber(randomNeighbour, i);
            randomNeighbour = rand.nextInt(4);
            ereaseWallsNumber(randomNeighbour, i);

        }

    }

    private void ereaseWallsNumber(int randomWall, int i) {
        switch (randomWall) {
            case 0: // top neighbour
                maze.get(i).setUp(false);
                maze.get(i - WIDTH).setDown(false);
                break;
            case 1:
                maze.get(i).setRight(false);
                maze.get(i + 1).setLeft(false);
                break;
            case 2:
                maze.get(i).setDown(false);
                maze.get(i + WIDTH).setUp(false);
                break;
            case 3:
                maze.get(i).setLeft(false);
                maze.get(i - 1).setRight(false);
                break;
        }
    }

    /**
     * Cheks if given position can be placed in maze
     *
     * @param aX x coordinate
     * @param aY y coordinate
     * @return true if position is correct
     * @throws PositionException exception
     */
    public boolean checkPositionBounds(int aX, int aY) throws PositionException {
        if (aX < 0 | aY < 0 | aX > this.WIDTH | aY > this.HEIGHT) {
            throw new PositionException("Invalid position");
        } else {
            return true;
        }

    }

    /**
     * Checks if maze was reseted corrctly - every cell is in default state
     *
     * @return true if maze is reseted
     */
    public boolean checkIfResetedCorrectly() {
        for (Cell i : maze) {
            if (i.isDefault() == false) {
                return false;
            }
        }
        return true;
    }

}
