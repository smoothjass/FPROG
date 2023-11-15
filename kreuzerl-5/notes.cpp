auto generate_ints = [](const int min, const int max)
{
    random_device rd;        // use for generating the seed
    mt19937 generator(rd()); // used for generating pseudo-random
    numbers
        uniform_int_distribution<int>
            distribution(min, max); // used to generate uniformly distributed numbers between min and max
    auto values = transformAll<vector<int>>(
        range(0, 98), // generates the range[0..98]
        [&distribution, &generator](auto)
        {
            return distribution(generator); // generate the random numbers
        });
    values.push_back(min); // ensure that min and max values are included
    values.push_back(max);
    return values;
};

auto generate_ints_greater_than_1 = bind(generate_ints, 1,
                                         numeric_limits<int>::max());

auto check_property = [](const auto &generator, const auto &property, const string &generatorName)
{
    auto values = generator();
    CHECK(all_of_collection(values, property));
};

auto prop_0_to_any_nonzero_int_is_0 = [](const int exponent)
{
    CHECK(exponent > 0); // checking the contract just to be sure
    return power(0, exponent) == 0;
};

TEST_CASE("Properties")
{
    // cout << "Property: 0 to power 0 is 1" << endl;
    // CHECK(property_0_to_power_0_is_1);
    cout << "Property: 0 to [1..maxInt] is 0" << endl;
    check_property(generate_ints_greater_than_1,
                   prop_0_to_any_nonzero_int_is_0, "generate ints");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("lines")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Line expectedLine0{'X', 'X', 'X'};
    CHECK_EQ(expectedLine0, line(board, 0));
    Line expectedLine1{' ', 'O', ' '};
    CHECK_EQ(expectedLine1, line(board, 1));
    Line expectedLine2{' ', ' ', 'O'};
    CHECK_EQ(expectedLine2, line(board, 2));
}

TEST_CASE("all columns")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Line expectedColumn0{'X', ' ', ' '};
    CHECK_EQ(expectedColumn0, column(board, 0));
    Line expectedColumn1{'X', 'O', ' '};
    CHECK_EQ(expectedColumn1, column(board, 1));
    Line expectedColumn2{'X', ' ', 'O'};
    CHECK_EQ(expectedColumn2, column(board, 2));
}

TEST_CASE("main diagonal")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Line expectedDiagonal{'X', 'O', 'O'};

    CHECK_EQ(expectedDiagonal, mainDiagonal(board));
}

TEST_CASE("secondary diagonal")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Line expectedDiagonal{'X', 'O', ' '};

    CHECK_EQ(expectedDiagonal, secondaryDiagonal(board));
}

TEST_CASE("all lines, columns and diagonals")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Lines expected{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'},
        {'X', ' ', ' '},
        {'X', 'O', ' '},
        {'X', ' ', 'O'},
        {'X', 'O', 'O'},
        {'X', 'O', ' '}};

    auto all = allLinesColumnsAndDiagonals(board);
    CHECK_EQ(expected, all);
}

TEST_CASE("line to string")
{
    Line line{
        ' ', 'X', 'O'};

    CHECK_EQ(" XO", lineToString(line));
}

TEST_CASE("board to lines string")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};
    vector<string> expected{
        "XXX",
        " O ",
        "  O"};

    CHECK_EQ(expected, boardToLinesString(board));
}

TEST_CASE("board to string")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};
    string expected{"XXX\n O \n  O\n"};

    CHECK_EQ(expected, boardToString(board));
}

TEST_CASE("Line filled with X")
{
    Line line{'X', 'X', 'X'};

    CHECK(lineFilledWithX(line));
}

TEST_CASE("Line not filled with X")
{
    CHECK(!lineFilledWithX(Line({'X', 'O', 'X'})));
    CHECK(!lineFilledWithX(Line({'X', ' ', 'X'})));
}

TEST_CASE("X wins")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    CHECK(xWins(board));
}

TEST_CASE("O wins")
{
    Board board{
        {'X', 'O', 'X'},
        {' ', 'O', ' '},
        {' ', 'O', 'X'}};

    CHECK(oWins(board));
}

TEST_CASE("draw")
{
    Board board{
        {'X', 'O', 'X'},
        {'O', 'O', 'X'},
        {'X', 'X', 'O'}};

    CHECK(draw(board));
}

TEST_CASE("in progress")
{
    Board board{
        {'X', 'O', 'X'},
        {'O', ' ', 'X'},
        {'X', 'X', 'O'}};

    CHECK(inProgress(board));
}

TEST_CASE("how did X win")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    CHECK_EQ("first line", howDidXWin(board));
}

TEST_CASE("X did not win")
{
    Board board{
        {'X', 'X', ' '},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    CHECK_EQ("X did not win", howDidXWin(board));
}

TEST_CASE("Project column")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    Line expected0{'X', ' ', ' '};
    CHECK_EQ(expected0, column(board, 0));
    Line expected1{'X', 'O', ' '};
    CHECK_EQ(expected1, column(board, 1));
    Line expected2{'X', ' ', 'O'};
    CHECK_EQ(expected2, column(board, 2));
}

TEST_CASE("Range")
{
    Board board{
        {'X', 'X', 'X'},
        {' ', 'O', ' '},
        {' ', ' ', 'O'}};

    vector<int> expected = {0, 1, 2};
    CHECK_EQ(expected, toRange(board));
    CHECK_EQ(expected, toRange(board[0]));
}

TEST_CASE("difference in num <= 1")
{
    Board board{
        {' ', ' ', ' '},
        {' ', 'X', ' '},
        {' ', 'O', 'X'}};
    CHECK(differenceInNumOfTokens(boardToString(board)) <= 1);
}

TEST_CASE("difference in num > 1")
{
    Board board{
        {' ', ' ', 'X'},
        {' ', 'X', ' '},
        {' ', 'O', 'X'}};
    CHECK_FALSE(differenceInNumOfTokens(boardToString(board)) <= 1);
}

TEST_CASE("correct tokens")
{
    Board board{
        {' ', ' ', 'X'},
        {' ', 'X', ' '},
        {' ', 'O', 'X'}};
    CHECK(containsOnlyValidTokens(boardToString(board)));
}

TEST_CASE("wrong tokens")
{
    Board board{
        {' ', '8', 'X'},
        {' ', 'X', 'X'},
        {' ', 'O', 'X'}};
    CHECK_FALSE(containsOnlyValidTokens(boardToString(board)));
}

TEST_CASE("wrong board dimension")
{
    Board board{
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X'}};
    CHECK_FALSE(validBoardSize(board));
}

TEST_CASE("wrong board dimension")
{
    Board board{
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X'},
        {'X', 'X', 'X', 'X'}};
    CHECK_FALSE(validBoardSize(board));
}

TEST_CASE("wrong board dimension")
{
    Board board{
        {'X', 'X', 'X'},
        {'X', 'X', 'X'},
        {'X', 'X', 'X'},
        {'X', 'X', 'X'}};
    CHECK_FALSE(validBoardSize(board));
}

TEST_CASE("correct board dimension")
{
    Board board{
        {'X', 'X', 'X'},
        {'X', 'X', 'X'},
        {'X', 'X', 'X'}};
    CHECK(validBoardSize(board));
}