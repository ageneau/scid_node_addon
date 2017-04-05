{
  'variables' : {
    'project_root': './deps/scid/'
  },

  'target_defaults': {
    'include_dirs': [
      '<(project_root)/src',
      'node',
    ],

    'defines': [
      'NODEJS',
    ],

    "link_settings": {
      'ldflags': [
          # '-Wl,-no-undefined',
      ],
    }
  },

  'targets': [
    {
      'target_name': 'scid',
      'sources': [
        '<(project_root)/src/bytebuf.cpp',
        '<(project_root)/src/date.cpp',
        '<(project_root)/src/dstring.cpp',
        '<(project_root)/src/filter.cpp',
        '<(project_root)/src/game.cpp',
        '<(project_root)/src/gfile.cpp',
        '<(project_root)/src/index.cpp',
        '<(project_root)/src/matsig.cpp',
        '<(project_root)/src/mfile.cpp',
        '<(project_root)/src/misc.cpp',
        '<(project_root)/src/namebase.cpp',
        '<(project_root)/src/pgnparse.cpp',
        '<(project_root)/src/position.cpp',
        '<(project_root)/src/sortcache.cpp',
        '<(project_root)/src/stored.cpp',
        '<(project_root)/src/textbuf.cpp',
        '<(project_root)/src/scidbase.cpp',
        '<(project_root)/src/dbasepool.cpp',
        '<(project_root)/src/sc_base.cpp',
        '<(project_root)/src/tkscid.cpp',
        '<(project_root)/src/polyglot/attack.cpp',
        '<(project_root)/src/polyglot/board.cpp',
        '<(project_root)/src/polyglot/book.cpp',
        '<(project_root)/src/polyglot/colour.cpp',
        '<(project_root)/src/polyglot/fen.cpp',
        '<(project_root)/src/polyglot/hash.cpp',
        '<(project_root)/src/polyglot/list.cpp',
        '<(project_root)/src/polyglot/main.cpp',
        '<(project_root)/src/polyglot/move.cpp',
        '<(project_root)/src/polyglot/move_do.cpp',
        '<(project_root)/src/polyglot/move_gen.cpp',
        '<(project_root)/src/polyglot/move_legal.cpp',
        '<(project_root)/src/polyglot/option.cpp',
        '<(project_root)/src/polyglot/piece.cpp',
        '<(project_root)/src/polyglot/random.cpp',
        '<(project_root)/src/polyglot/san.cpp',
        '<(project_root)/src/polyglot/square.cpp',
        '<(project_root)/src/polyglot/util.cpp',
        'node/jsscid.cpp',
      ],
    },
  ],
}
