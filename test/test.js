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
