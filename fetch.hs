module Main where

import Foreign (allocaArray0)
import Foreign.C
import System.Environment (getEnv)

main :: IO ()
main = do
  putThreeStrLn "(\\_/) \ESC[33m     uptime:      " "\ESC[0m" =<< uptime
  putThreeStrLn "(oᴥo) \ESC[31m     shell:       " "\ESC[0m" =<< shell
  putThreeStrLn "|U°U| \ESC[35m     distro:      " "\ESC[0m" . emptyMaybe =<< os
  putThreeStrLn "|   | \ESC[34m     hostname:    " "\ESC[0m" =<< hostname
  putThreeStrLn "'U_U' \ESC[36m     kernel:      " "\ESC[0m" =<< kernel
  putStrLn "  U"

putThreeStrLn :: String -> String -> String -> IO ()
putThreeStrLn a c b = putStr a >> putStr b >> putStrLn c

uptime :: IO String
-- TODO: formatting
uptime = do
  time <- upto '.' <$> readFile "/proc/uptime"
  let t = read time
      seconds = pshow $ mod t 60
      minutes = pshow $ mod (div t 60) 60
      hours = pshow $ div t 3600
  return $ hours ++ ':' : minutes ++ ':' : seconds
  where
    pshow a
      | a < 10 = '0' : show a
      | otherwise = show a

shell :: IO String
shell = getEnv "SHELL"

os :: IO (Maybe String)
os = do
  lines <- lines <$> readFile "/etc/os-release"
  return . fmap init . first . map (flip isPrefixStrip "PRETTY_NAME=\"") $ lines
  where
    isPrefixStrip [] [] = Just ""
    isPrefixStrip [] (b : bs) = Nothing
    isPrefixStrip (a : as) [] = Just (a : as)
    isPrefixStrip (a : as) (b : bs)
      | a == b = isPrefixStrip as bs
      | otherwise = Nothing

foreign import ccall unsafe "gethostname" gethostname :: CString -> CSize -> IO CInt

-- I don't know which implementation is better
hostname :: IO String
hostname = do
  hname <- readFile "/etc/hostname"
  return . init $ hname

-- hostname = allocaArray0 size $ \cstr -> do
--   throwErrnoIfMinus1_ "gethostname" $ gethostname cstr (fromIntegral size)
--   peekCString cstr
--   where
--     size = 256

kernel :: IO String
kernel = return . upto '(' =<< readFile "/proc/version"

upto a (b : bs)
  | a == b = []
  | otherwise = b : (upto a bs)
upto _ [] = []

maybeHead :: [a] -> Maybe a
maybeHead (a : _) = Just a
maybeHead [] = Nothing

first :: [Maybe a] -> Maybe a
first ((Just a) : as) = Just a
first (Nothing : as) = first as
first [] = Nothing

emptyMaybe :: Maybe String -> String
emptyMaybe (Just a) = a
emptyMaybe Nothing = ""