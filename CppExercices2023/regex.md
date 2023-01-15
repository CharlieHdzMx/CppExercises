* bool regex_search( string<CharT,STraits,SAlloc>& s,
                   basic_regex<CharT,Traits>& e,
                    flags =  std::regex_constants::match_default );
    * Determina si hay un match entre regular expression "e" y un subsecuente  en el caracter target sequence.
        * Returna true si hay un match de cualquier subsequence, retorna false si no.
* bool refez_match() es igual que regex_search pero retorna true solamente si todo el string tiene un match con el regex.
