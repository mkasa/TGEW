# -*- python -*-
APPNAME = 'TGEW'
VERSION = '1.08'

def set_options(ctx):
    ctx.tool_options('compiler_cc')

def configure(conf):
    conf.check_tool('compiler_cc')

def build(bld):
    # print bld.env
    bld.env.CCFLAGS.append('-DPREFIX_DIR="' + bld.env.PREFIX + '"')
    bld(features='cc cprogram',
        source='atomicappend.c',
        target='atomicappend')
    bld.install_files('${PREFIX}/lib/perl5', ['TGEW.pm'])
    bld.install_files('${PREFIX}/bin', ['qtop', 'qfree', 'qsisub', 'tge_del', 'tge_stat', 'tge_temp', 'tge_make', 'tge_sub', 'tge_install'], chmod=0755)


