# @param {String[]} words
# @param {Integer} max_width
# @return {String[]}
def full_justify(words, max_width)
    answer = []
    while words.size > 0
        # Starting backwards, try to fit as many words as possible in this line.
        words.size.downto(0) do |num_words|
            tokens = words.first(num_words)
            used = tokens.sum(&:size)
            if used + num_words - 1 <= max_width
                # Found a winner!
                if num_words == words.size || num_words == 1
                    # Corner case. Only one word or last line.
                    answer << tokens.join(" ").ljust(max_width)
                else
                    # More than two words.
                    spaces = max_width - used  # Total spaces that need to be distributed.
                    buckets = num_words - 1   # Number of "buckets" between words to distribute the spaces.
                    tokens_with_spaces = tokens.first(spaces % buckets).map do |t|
                        t + " " * (spaces / buckets + 1)
                    end + tokens.drop(spaces % buckets)[0...-1].map do |t|
                        t + " " * (spaces / buckets)
                    end + tokens.last(1)
                    answer << tokens_with_spaces.join("")
                end

                words = words.drop(num_words)
                break
            end
        end
    end
    return answer
end
