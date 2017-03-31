'use strict';

var res, baseId, numGames, gameId;
var assert = require('assert');
var scid = require(__dirname + "/..");

var fn = __dirname + '/TestDB';

describe('base', function() {
  baseId = scid.base("open", fn);
  it('should return the base id', function () {
    assert.equal(1, baseId);
  });
  numGames = scid.base("numGames", baseId);
  it('should return the number of games in the databases', function () {
    assert.equal(4, numGames);
  });
});

describe('filter', function() {
  it('should return the number of games found with the current filter', function () {
    assert.equal(4, scid.filter("count", baseId, "dbfilter"));
  });
  it('should return the number of games in the databases', function () {
    assert.equal(4, numGames);
  });
});

describe('game', function() {
  gameId = 2;
  it('should return the same game id we requested', function () {
    scid.game("load", gameId);
    assert.equal(gameId, scid.game("number"));
  });
  it('should contain the pgn for the game Akopian - Volokitin', function () {
    assert.notEqual(-1, scid.game("pgn").indexOf("Akopian, Vl"));
  });
  it('should contain the name of the white player', function () {
    assert.equal("Akopian, Vl", scid.game("info", "white"));
  });
  it('should contain the ELO rating of the black player', function () {
    assert.equal(2709, scid.game("info", "belo"));
  });
});

describe('search', function() {
  it('should return the number of games with a position where a black knight is on b4', function() {
    var result = scid.search("material",
                             "-wq","0 2",
                             "-bq","0 2",
                             "-wr","0 2",
                             "-br","0 2",
                             "-wb","0 2",
                             "-bb","0 2",
                             "-wn","0 2",
                             "-bn","0 2",
                             "-wm","0 4",
                             "-bm","0 4",
                             "-wp","0 8",
                             "-bp","0 8",
                             "-flip","0",
                             "-filter","2",
                             "-range","1 999",
                             "-length","1",
                             "-bishops","Either",
                             "-diff","-40 +40",
                             "-patt","Yes bn b 4",
                             "-patt","Yes ? ? ?",
                             "-patt","Yes ? ? ?",
                             "-patt","Yes ? ? ?",
                             "-patt","Yes ? ? ?",
                             "-patt","Yes ? ? ?",
                             "-patt","Yes ? ? ?",
                             "-patt","Yes ? ? ?",
                             "-patt","Yes ? ? ?",
                             "-patt","Yes ? ? ?");
    assert.notEqual(-1, result.startsWith("4 / 4"));
  });
});
