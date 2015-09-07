This is another way to more robustly read an integer from a std::stream
by ignoring invalid characters after the reading of an int failed
and trying again. As one option it shows how to ignore input characters
up to a line break (regardless of how long the line might be).