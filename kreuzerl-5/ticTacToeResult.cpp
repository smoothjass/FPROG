#include <iostream>
#include <functional>
#include <optional>
#include <string>
#include <numeric>
#include <random>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;

using Line = vector<char>;
using Board = vector<Line>;
using Lines = vector<Line>;

template <typename DestinationType>
auto transformAll = [](const auto &source, auto fn)
{
    DestinationType result;
    result.reserve(source.size());
    transform(source.begin(), source.end(), back_inserter(result), fn);
    return result;
};

auto toRange = [](const auto &collection)
{
    vector<int> range(collection.size());
    iota(begin(range), end(range), 0);
    return range;
};

auto accumulateAll = [](const auto source, auto fn)
{
    return accumulate(source.begin(), source.end(), typename decltype(source)::value_type(), fn);
};

auto all_of_collection = [](const auto &collection, auto fn)
{
    return all_of(collection.begin(), collection.end(), fn);
};

auto any_of_collection = [](const auto &collection, auto fn)
{
    return any_of(collection.begin(), collection.end(), fn);
};

auto lineToString = [](const auto &line)
{
    return transformAll<string>(line, [](auto const token) -> char
                                { return token; });
};

auto boardToLinesString = [](const auto &board)
{
    return transformAll<vector<string>>(board, lineToString);
};

auto boardToString = [](const auto &board)
{
    const auto linesAsString = boardToLinesString(board);
    return accumulateAll(linesAsString,
                         [](string current, string lineAsString)
                         { return current + lineAsString + "\n"; });
};

auto concatenate = [](const auto &first, const auto &second)
{
    auto result{first};
    result.insert(result.end(), make_move_iterator(second.begin()), make_move_iterator(second.end()));
    return result;
};

auto concatenate3 = [](const auto &first, const auto &second, const auto &third)
{
    return concatenate(concatenate(first, second), third);
};

using Coordinate = pair<int, int>;

auto accessAtCoordinates = [](const auto &board, const Coordinate &coordinate)
{
    return board[coordinate.first][coordinate.second];
};

auto projectCoordinates = [](const auto &board, const auto &coordinates)
{
    const auto boardElementFromCoordinates = bind(accessAtCoordinates, board, _1);
    return transformAll<Line>(coordinates, boardElementFromCoordinates);
};

auto mainDiagonalCoordinates = [](const auto &board)
{
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [](const auto &index)
                                            { return make_pair(index, index); });
};

auto secondaryDiagonalCoordinates = [](const auto &board)
{
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [board](auto index)
                                            { return make_pair(index, board.size() - index - 1); });
};

auto columnCoordinates = [](const auto &board, const auto &columnIndex)
{
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [columnIndex](const auto &index)
                                            { return make_pair(index, columnIndex); });
};

auto lineCoordinates = [](const auto &board, const auto &lineIndex)
{
    const auto range = toRange(board);
    return transformAll<vector<Coordinate>>(range, [lineIndex](const auto &index)
                                            { return make_pair(lineIndex, index); });
};

auto mainDiagonal = [](const auto &board)
{
    return projectCoordinates(board, mainDiagonalCoordinates(board));
};

auto secondaryDiagonal = [](const auto &board)
{
    return projectCoordinates(board, secondaryDiagonalCoordinates(board));
};

auto column = [](const auto &board, const auto &columnIndex)
{
    return projectCoordinates(board, columnCoordinates(board, columnIndex));
};

auto line = [](const auto &board, const int lineIndex)
{
    return projectCoordinates(board, lineCoordinates(board, lineIndex));
};

auto allLines = [](const auto &board)
{
    const auto range = toRange(board);
    return transformAll<Lines>(range, [board](auto index)
                               { return line(board, index); });
};

auto allColumns = [](const auto &board)
{
    const auto range = toRange(board);
    return transformAll<Lines>(range, [board](auto index)
                               { return column(board, index); });
};

auto allDiagonals = [](const auto &board) -> Lines
{
    return {mainDiagonal(board), secondaryDiagonal(board)};
};

template <typename SourceType, typename DestinationType>
auto applyAllLambdasToValue = [](const auto &fns, const auto &value)
{
    return transformAll<DestinationType>(fns, [value](const auto &fn)
                                         { return fn(value); });
};

auto allLinesColumnsAndDiagonals = [](const auto &board)
{
    return concatenate3(allLines(board), allColumns(board), allDiagonals(board));
};

auto lineFilledWith = [](const auto &line, const auto &tokenToCheck)
{
    return all_of_collection(line, [&tokenToCheck](const auto &token)
                             { return token == tokenToCheck; });
};

auto lineFilledWithX = bind(lineFilledWith, _1, 'X');
auto lineFilledWithO = bind(lineFilledWith, _1, 'O');

template <typename CollectionBooleanOperation, typename CollectionProvider, typename Predicate>
auto booleanOperationOnProvidedCollection(CollectionBooleanOperation collectionBooleanOperation, CollectionProvider collectionProvider, Predicate predicate)
{
    return [=](auto collectionProviderSeed, auto predicateFirstParameter)
    {
        return collectionBooleanOperation(collectionProvider(collectionProviderSeed),
                                          bind(predicate, _1, predicateFirstParameter));
    };
}

auto tokenWins = booleanOperationOnProvidedCollection(any_of_collection, allLinesColumnsAndDiagonals, lineFilledWith);
auto xWins = bind(tokenWins, _1, 'X');
auto oWins = bind(tokenWins, _1, 'O');

/*auto xWins = [](const auto& board){
    return any_of_collection(allLinesColumnsAndDiagonals(board), lineFilledWithX);
};

auto oWins = [](const auto& board){
    return any_of_collection(allLinesColumnsAndDiagonals(board), lineFilledWithO);
};
*/

/* auto noneOf = [](const auto& collection, const auto& fn){
    return none_of(collection.begin(), collection.end(), fn);
};*/

// auto isEmpty = [](const auto& token){return token == ' ';};

auto isNotEmpty = [](const auto &token)
{ return token != ' '; };

auto fullLine = bind(all_of_collection, _1, isNotEmpty);

auto full = [](const auto &board)
{
    return all_of_collection(board, fullLine);
};

auto draw = [](const auto &board)
{
    return full(board) && !xWins(board) && !oWins(board);
};

auto inProgress = [](const auto &board)
{
    return !full(board) && !xWins(board) && !oWins(board);
};

auto findInCollection = [](const auto &collection, const auto &fn)
{
    const auto result = find_if(collection.begin(), collection.end(), fn);
    return (result == collection.end()) ? nullopt : optional(*result);
};

auto findInCollectionWithDefault = [](const auto &collection, const auto &defaultResult, const auto &fn)
{
    const auto result = findInCollection(collection, fn);
    return result.has_value() ? (*result) : defaultResult;
};

auto howDidXWin = [](auto const board)
{
    map<string, Line> linesWithDescription{
        {"first line", line(board, 0)},
        {"second line", line(board, 1)},
        {"last line", line(board, 2)},
        {"first column", column(board, 0)},
        {"second column", column(board, 1)},
        {"last column", column(board, 2)},
        {"main diagonal", mainDiagonal(board)},
        {"secondary diagonal", secondaryDiagonal(board)},
        {"diagonal", secondaryDiagonal(board)},
    };
    auto xDidNotWin = make_pair("X did not win", Line{});
    auto xWon = [](auto value)
    {
        return lineFilledWithX(value.second);
    };

    return findInCollectionWithDefault(linesWithDescription, xDidNotWin, xWon).first;
};

auto differenceInNumOfTokens = [](const auto &collection) -> int
{
    return abs(int(
        count_if(collection.begin(), collection.end(), [](char c)
                 { return c == 'X'; }) -
        count_if(collection.begin(), collection.end(), [](char c)
                 { return c == 'O'; })));
};

auto containsOnlyValidTokens = [](const auto &str)
{
    return str.find_first_not_of("XO \n") == std::string::npos;
};

auto validBoardSize = [](const auto &board)
{
    return (
        board.size() == 3
        //&& (board[0].size() == 3 && board[1].size() == 3 && board[2].size() == 3)
        && all_of_collection(board, [](const auto &line)
                             { return line.size() == 3; }));
};

/*Please implement data generators for property based testing for the TIC-TAK-TOE game.

These generators shall produce:

    fully filled correct boards
    fully filled erroneous boards (with wrong tokens e.g. 'A" instead of X, O, ...
    partially filled correct boards
    partially filled erroneous boards (e.g. 4 X's and only 2 O's)
    correct-winning boards

the functions in "correct and erroneous" should not be redundant.*/

// from the book:
auto range = [](const int minValue, const int maxValue)
{
    vector<int> range(maxValue - minValue + 1);
    iota(range.begin(), range.end(), minValue);
    return range;
};

auto generate_boards = [](const std::vector<char> &usingCharacters, const bool& checkForTokenCount)
{
    random_device rd;        // use for generating the seed
    mt19937 generator(rd()); // used for generating pseudo-random numbers
        uniform_int_distribution<int>
            distribution(0, usingCharacters.size() - 1); // used to generate uniformly distributed
                                                         // numbers between first and last index
    std::vector<Board> boards;
    for (int i = 0; i < 50; ++i)
    {
        auto values = transformAll<vector<int>>(
            range(0, 9), // generates the range[0..9] -> one board
            [&distribution, &generator](auto)
            {
                return distribution(generator); // generate the random numbers
            });
        Board board = {
            {usingCharacters[values[0]], usingCharacters[values[1]], usingCharacters[values[2]]},
            {usingCharacters[values[3]], usingCharacters[values[4]], usingCharacters[values[5]]},
            {usingCharacters[values[6]], usingCharacters[values[7]], usingCharacters[values[8]]}};
        if(checkForTokenCount){
            if(differenceInNumOfTokens(boardToString(board)) > 1) --i;
            else boards.push_back(board);
        }
        else {
            if(differenceInNumOfTokens(boardToString(board)) > 1) boards.push_back(board);
            else --i;
        }
    }
    return boards;
};

auto check_property = [](const auto &generator, const auto &property)
{
    auto values = generator();
    CHECK(all_of_collection(values, property));
};

auto isBoardCorrect = [](const Board& board)
{
    return containsOnlyValidTokens(boardToString(board));
};

auto isBoardFalse = [](const Board& board)
{
    return !containsOnlyValidTokens(boardToString(board));
};

auto isBoardUnbalanced = [](const Board& board)
{
    return differenceInNumOfTokens(boardToString(board)) > 1;
};

auto isBoardBalanced = [](const Board& board)
{
    return differenceInNumOfTokens(boardToString(board)) <= 1;
};

TEST_CASE("Board Properties")
{
    std::vector<char> validCharactersFullBoard = {'X', 'O'};
    auto generateValidFullBoard = bind(generate_boards, validCharactersFullBoard, true);
    check_property(generateValidFullBoard, isBoardCorrect);
    check_property(generateValidFullBoard, isBoardBalanced);

    std::vector<char> validCharactersPartiallyFilledBoard = {'X', 'O', ' '};
    auto generateValidPartiallyFilledBoard = bind(generate_boards, validCharactersPartiallyFilledBoard, true);
    check_property(generateValidPartiallyFilledBoard, isBoardCorrect);
    check_property(generateValidPartiallyFilledBoard, isBoardBalanced);

    std::vector<char> invalidCharactersFullBoard = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
    'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'Y', 'Z'};
    auto generateInvalidFullBoard = bind(generate_boards, invalidCharactersFullBoard, true);
    check_property(generateInvalidFullBoard, isBoardFalse);

    auto generateInvalidPartiallyFilledBoard = bind(generate_boards, validCharactersPartiallyFilledBoard, false);
    check_property(generateInvalidPartiallyFilledBoard, isBoardUnbalanced);
}