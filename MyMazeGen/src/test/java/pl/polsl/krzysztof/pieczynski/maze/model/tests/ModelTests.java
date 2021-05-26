/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.krzysztof.pieczynski.maze.model.tests;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.RepeatedTest;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;
import org.junit.jupiter.params.provider.ValueSource;
import pl.polsl.krzsztof.pieczynski.maze.model.MazeModel;
import pl.polsl.krzsztof.pieczynski.maze.model.MazeModel.Location;
import pl.polsl.krzsztof.pieczynski.maze.model.User;

/**
 *
 * @author piecz
 */
public class ModelTests {

    public ModelTests() {
    }

    MazeModel model;

    @BeforeEach
    public void setUp() {
        User user = new User("default");
        model = new MazeModel(10, 10, user);
        model.generateMaze();
        model.setAllCellsUnvisited();
    }

    /**
     * Tesing if GenerateMaze works properly. Searching for fail of an algorithm
     * - stack overflow, vector out of range etc.
     */
    @RepeatedTest(10)
    public void testForGeneratingMaze() {

        model.resetMaze();
        model.generateMaze();
    }

    /**
     * Test if reseting maze works, after resetMaze all Cells have to be in
     * default state
     */
    @RepeatedTest(10)
    public void testForClearingMaze() {
        //GIVEN
        model.generateMaze();
        model.resetMaze();
        //WHEN
        boolean isResetedCorrectly = model.checkIfResetedCorrectly();
        //THEN
        assertEquals(isResetedCorrectly, true, "Path wasn't found");
    }

    /*
   @ParameterizedTest
 @ValueSource(ints = {1, 2, 3, 4, 5, 6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24}) // six numbers
void isBorderIndexOrNo(int givenIndex) {
    List<Integer> correctValues = List.of(1,2,3,4,5,10,15,20,9,14,19,24,21,22,23,24);
    boolean correctAnswer = correctValues.contains(givenIndex);
    boolean result = model.checkIfBorderIndex(givenIndex);
   assertEquals(result, correctAnswer, "Wrong");
}
    
     */
    /**
     * Checking if BFSurdl algorithm can find path from starting to ending point
     * in the maze
     *
     * @param sX Start x coordinate
     * @param sY Start y cooridnate
     * @param eX End x coordinate
     * @param eY End Y coordinate
     * @param expected Expected value returned by algorithm
     */
    @ParameterizedTest
    @MethodSource("providePairsForSolving")
    void checkIfSolvedBFSurdl(int sX, int sY, int eX, int eY, boolean expected) {
        //GIVEN
        List<Integer> path = new ArrayList();
        //WHEN

        boolean ifSolved = model.BFSurdl(Location.None, sX, sY, eX, eY, path);
        //THEN
        assertEquals(ifSolved, expected, "Path wasn't found");
    }

    /**
     * Checking if BFSdrlu algorithm can find path from starting to ending point
     * in the maze
     *
     * @param sX Start x coordinate
     * @param sY Start y cooridnate
     * @param eX End x coordinate
     * @param eY End Y coordinate
     * @param expected Expected value returned by algorithm
     */
    @ParameterizedTest
    @MethodSource("providePairsForSolving")
    void checkIfSolvedBFSdrlu(int sX, int sY, int eX, int eY, boolean expected) {
        //GIVEN
        List<Integer> path = new ArrayList();
        //WHEN
        boolean ifSolved = model.BFSdrlu(Location.None, sX, sY, eX, eY, path);
        //THEN
        assertEquals(ifSolved, expected, "Path wasn't found");
    }

    /**
     * Checking if Astar algorithm can find path from starting to ending point
     * in the maze
     *
     * @param sX Start x coordinate
     * @param sY Start y cooridnate
     * @param eX End x coordinate
     * @param eY End Y coordinate
     * @param expected Expected value returned by algorithm
     */
    @ParameterizedTest
    @MethodSource("providePairsForSolving")
    void checkIfSolvedAstar(int sX, int sY, int eX, int eY, boolean expected) {
        //GIVEN
        List<Integer> path = new ArrayList();
        //WHEN
        boolean if_solved = model.Astar(sX, sY, eX, eY, path);
        //THEN
        assertEquals(if_solved, expected, "Path wasn't found");
    }

    /**
     * Creates stream of values for testing solving algorithms
     *
     * @return Stream of values as StartX, StartY, EndX, EndY,
     * ExpectedValueReturnedByAlgorithm
     */
    private static Stream<Arguments> providePairsForSolving() {
        return Stream.of(
                Arguments.of(1, 2, 1, 2, true),
                Arguments.of(1, 3, 1, 8, true),
                Arguments.of(2, 1, 5, 4, true),
                Arguments.of(1, 2, 11, 12, false)
        );
    }
}
