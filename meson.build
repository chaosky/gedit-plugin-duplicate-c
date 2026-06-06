project('gedit-duplicate-line', 'c', version: '1.0')

gedit_dep = dependency('gedit')
peas_dep = dependency('libpeas-1.0')

shared_module('duplicateline',
  'duplicateline.c',
  dependencies: [gedit_dep, peas_dep],
  install: true,
  install_dir: get_option('prefix') / 'lib64' / 'gedit' / 'plugins',
)

install_data('duplicateline.plugin',
  install_dir: get_option('prefix') / 'lib64' / 'gedit' / 'plugins',
)
