<?php
include_once '../include/base.php';

// $packetcode = new PacketCode();

// $codecontent = file_get_contents('example_packetcode.txt');
// $packetcode->get_formatcode($codecontent);
// $packetcode->create_codefile();

/**
 * 从目录生成包的代码
 * @param string $indir
 * @param string $outdir
 */
function createcode_fromdir($indir = NULL, $outdir = NULL) {
  if (NULL == $indir || NULL == $outdir) return false;
  $starttime = time();
  $totalfile = 0;
  $successfile = 0;
  $formatcode_files = glob($indir.'*.txt');
  $totalfile = count($formatcode_files);
  if (0 === $totalfile) return false;
  $packetcode = new PacketCode();
  foreach ($formatcode_files as $file) {
    $codecontent = file_get_contents($file);
    $packetcode->get_formatcode($codecontent);
    $result = $packetcode->create_codefile($outdir);
    if (true === $result) ++$successfile;
  }
  $endtime = time();
  echo 'create code completed, use time: ',$endtime - $starttime,'s',LF;
  echo 'toalfile: ',$totalfile,' success file: ',$successfile,LF;
  unset($packetcode);
}

/**
 * enter function
 * @param void
 * @return void
 */
function main() {
  $argc = $GLOBALS['argc'];
  $argv = $GLOBALS['argv'];
  $outputdir = './packet/code';
  $indir = './packet/txt';
  if (3 === $argc) {
    list($indir, $outputdir) = $argv;
  }
  createcode_fromdir(complementpath($indir), complementpath($outputdir));
}

main();