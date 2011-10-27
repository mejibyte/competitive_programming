module Main where

import IO

main = do
  hSetBuffering stdin LineBuffering
  process 0

process sum = do
  query <- getLine
  let n = read query
  if (n > 0)
    then do let sum' = sum + n
            putStrLn $ show sum'
            hFlush stdout
            process sum'
    else do putStr ""
