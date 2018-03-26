# human4b
**human4b** is a humanly computable stream cipher, with a round design that is simple enough for most people to master (notably one has to mostly keep no more than 3 numbers in your head during a round).

## How to test/use

Because this is not currently designed for practical use, but for cryptoanalysis, scrutiny and criticism, the less practical but more cryptoanalytically useful side of generating a keystream is revealed (if the keystream is strong there is no need for any other proof of strength).

### How to generate a keystream

First compile the program by running `make human4b`.
Next, run the following command:

`./human4b --hex 1`

Which should generate the following keystream:

`A6215D8D15102C25797961C439ECFC221E41B33D12520CC6C8E550418A241DBD6E82F756C461E61ADF8AA298CF40A96B7AE61D271E9DCA1E70C5F90AAB55AF9A8020E0254BAD496D245E67D1B74BDB74BFBE425B21212619E62B1BD0DD3EA00D3A5CB5D74C4766C906D61636D8558CC15E3000901FDB0FD074C689452FD1C170`

### Extra options / supplying an actual key

In place of the `--hex` I used above you can also use `--bin` which will simply print the binary characters equivalent to two keystream outputs (e.g. `01` will become one `1` byte).

The key (or seed) is in hex format (e.g. `FFFF` is a valid key) and **HAS** to be of length `3N + 1` where `N` is a natural number. This length is by design (to allow all pieces of the key to be added to the output stream). The other restriction is that the first key character cannot be `0`, the reason for this is that the cipher does not have any magic numbers, and there is simply no way to get from 0 to anything else for the first output character (the other characters of such a stream are fine, but the fact that the first one will always be `0` is obviously a vulnerability, which is why keys beginning with `0` are considered weak keys and should not be used).

### Test vectors (to make sure everything worked)
Running `./human4b --hex 1000000000000` gives output:

`A92A946338EBC3B78CF0B62D1F847E060A585BEA6CA67AB407108CC17141B4486F5F426D6929FDCA97B13B3BD4FE7FA15B6FC05BA601A59DC72E836330F62BC4D8276DFDA0ED2F242BC81B17614F1F290CD0996F04CF869299ADD7EABED1CF8CD9E3513D92F374A04963751240878B7CA607D08D53AEDBDD725A81A7D287A530`

Running `./human4b --hex 1000000000001` gives output:

`2CC9E7E87EDA0D004404573BBD8E5650DC01C3B7E67681A8695807681C42D95766073F3ECB3533E3EDC7A5FEDFF8601B15DDC511A9E8101404FFCE1C74B916DD4935EB8C073D219DF67654A625C0E6F6A5C78F3E9D81AE24C371D330F648767A088F27B0C676480B2B8B2BC80EE9BEB822467BD22D1F4EFE3CF341578FF5A080`

Running `./human4b --hex FFFF0000FFFF0000FFFF0000F` gives output:

`82813DEEFEBA13C5A5E00E678A56A409A4FF8AF8252BFBEA5505AE57F6DA72E384CA3EBF64012F2847CCDE24C76489E11C953C23B11A26B988DC1729E8D579FAD3B5E06F8A49DECE83F6BF33203BDB8327BA9DD65550854A16B24463A23DAA94B308C70A01BBF402F787F80A25DB5352ADABD3AC2825A5FA1178A0CB1AA4BFB0
`

## For analysis
### Diagrams (round design and key stream generation)

The total high-level process of key generation (described as a diagram) can be found [here](https://www.draw.io/?lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Key%20stream%20generation#R3Vpdc5s4FP01PKYDEgb8GCfp7sx2ZzvNw6aPipFBGxmxQtT2%2FvqVjMSXiOvWBjPtTB10JPRx7znSvbId%2BLDd%2F8ZRnv7JYkwd4MZ7Bz46AERhID8VcKgA3wMVkHASV5DXAM%2FkP6xBV6MliXHRaSgYo4LkXXDNsgyvRQdDnLNdt9mG0e6oOUqwBTyvEbXRv0ksUr0sEDb475gkqRnZC5ZVzStavyWclZkezwFwc%2FxXVW%2BR6UsvtEhRzHYtCD458IEzJqqn7f4BU2VaY7bqvY%2Fv1Nbz5jgT57yg3fIN0VIvPbp7JeJo2jITmOtpioMxzXFxWL3uOnC1S4nAzzlaq9qd5ILEUrGlsuTJR9075gLv352hV69b0gmzLRb8IJuYF6A2laaSKe4av4BAY2nLJwZDmgpJ3XNjDvmgLTJsnchaPY4lT3SRcZGyhGWIPjXoqmufli3wnogXBX9Y6NJXU5PJeVVVnh8Y4Kvu4lj4jDmR05f%2BqMB%2FsBAHrRtUCiahZjqfGMs7DlCzPm1%2BuUhW8rVuBbXkEE%2BwMeewkzimSJBv3d4vMTm0CPmR8EIR0lfyIqKYHSM9YFOyxq5NyeU0lDyXXy3qLvrE%2FTnu%2Bdfnnn71MyOZaNwIe24Ebs891RT0W42H7jlHh1azXDUoTo2z6NIlcnsOr3ps3F%2Bv8SxG%2BJZiPqF5CQaENxSMiTwm3MQjf9nWwp37wYXwNjv5YiQ1%2FagI%2FDAaVQQLSwR%2FYDU%2FZ7GS%2Fx9vLgHf88%2BQQDCSBMJxJABOaMA6DcbleWDz3LsJ0b1lP1y9LtHrxGG67WwGrlxe6MpzlWLCz2tbN5y1easscPojIRxVKYF1JHw55uW3Pgr66QPw7aPA98aKhsZJaVvsbhH6pU32pm5cfnsDyevFR8HZ5rXT1zoO8eYQhwS9UBwGA3GIPxL5anf9uuQbyF4nO7w8OxOsyQfmSD4%2FmpJ8%2Fi9PvoFk7%2BKj%2FWzyncjA4BzJF3hTku8GN8lB1L%2BEkHngTS4hvKGYc3EhMX8uO4uW3R0IXjfm9Oyg8%2BWvL7bvKSV5gb%2FPe1Tk1ddbG7JXTLhK%2FLnohQALWwjRgA6ia%2BhgpJuIU%2BmV3Phv%2F42KtxxBAmfvzcv5sxIsu7fkfjghK4PJWRmFs9mdqxBhDrtzHQ%2BaI%2FrKl8RmpXPWgQ%2B7tyKBO6EO7BhuJlcmoEuMcMorE2Dvng4IqBxhtWFH%2BjaWCf4tmam4K46KvZcNAMz3TaV8StTfR6ZUlxKpCLfMBFGD7rBSWZnJT1aqvtlGfrwdI%2BktklsCQdSM%2FspNTwaRS6mmZOCe36QHRNc5heDsDT8wytRmk7FM0X5DKO1BiJIkk8U1Pv4oBK6UP8ka0XtdsSVxTN%2FTTJcv1yBE1P06JRogBIiATYiaST%2FACFlsfpBTbTvNj57g0%2F8%3D).


The round design digram I have created (in probably pretty readable form), and it can be seen [here](https://www.draw.io/?lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Untitled%20Diagram.xml#R7Zpdb5swFIZ%2FTS43YTt8XW5d9yFtqrRerL10gwNsBDNiGrJfPwMGYux01ZrYEWovKnxsbPzyvIRjvEBXm%2FpTiYvkG41ItoBOVC%2FQhwWEge%2Fx%2F01g3wWWAHaBuEyjLgTGwG36h4igI6JVGpGt1JBRmrG0kIMrmudkxaQYLku6k5utaSaPWuCYKIHbFc7U6I80YomYFvTH%2BGeSxkk%2FMvDCruYBr37FJa1yMd4ConX711VvcN%2BXmOg2wRHdHYTQ9QJdlZSy7mhTX5GskbaXrTvv45Ha4bpLkrPnnCDu05bt%2B6mTiCshirRkCY1pjrPrMfq%2BnR5pOnB4KWGbjB8CfkjqlN014beuKN33NTkr9wdVTfFedPCTMLYXCOCKUR4ax%2F1KaSH66K60ubyjcxWhLa3KlWgluGO4jIlo5Q46c3wJ3RB%2BMbxJSTLM0ke5dyxAiod2o5j8QOip11YM%2FYizSnT6JS8qxkNAUV3WdJekjNwWuJ3EjjtM1ln0S0pG6qe1UGfZn%2BAIAIVBkSjuRtpBz2hyQLrnvFwX3zBzQCKubXde5pA95oCK1swMrRE3NCQuOmpoaN3QCNkzNFCnPzNHL%2B1BB9y5O1ojLkCG1F0etTSybmnXtWjppWnqTFvatUgdnP2vtE5dz5C6ruLpu5vvquBZxrNJ8m8n423RpZjrtG7kP8nrN5StDQLV24HG2sEJrD2knrOFL9TA5xuCL7x8%2BNDkdwUahA%2BEc4cPaBIUEBiiD6gpysXh5%2FqT15rQ4LNv9i%2FTwFPxg9AUfp6C3wJ6eNNQFbN2Tk%2BVLmFdbPLD7Ib%2Bs%2BDswXoRnKYXY42n0cC3CKfxdUfz3tfJayqn6Qf%2FX%2B%2Fbz7en70VGvR%2FM3vuBRTjR7HMerbxLU94PXuZ9aN3705dSo943nhOZ9j6EFuFEKl0z875OXnSE99O%2FVkGd97PG2Q%2F8oDd8G1jTnEl3wvtd0b7izbbV513zPIBFPVaOvQwd8Yvq%2BpL75%2BGDMW2nEsiVHim%2Br%2Ba5ruaRsjxBnouML98bZ16zzIKMrd%2BryyyvzLd3wJOZDzTfrM7G%2FPz3Mmm%2BlCJju5nUT6WvzLc8BzLzoWOQeaDclJuKXeomM%2BC4qjRn%2B4SN1If0oI39hGO6X8ewNuo30kEb%2Bwsx040PZ9WGF8fttm3dwZZmdP0X). All calculations work with 4-bit numbers. The other thing is I tried making the round function in the code readable, so if you prefer that feel free.

### Reasoning about security

I do not personally think this will turn out to be a strong PRNG, while the output (and diffusion) appears to be impressive at first sight, I can already find suspicious repeats, and some keys that appear to be weak, for example:

Previous suspicious stuff here was just a result of a typo in the code it appears and was not representative of the strength of the stream cipher.

### Design ideas

The 3 operations `+`, `xor` and `>>>` (right rotate) were chosen because addition is easy to compute modulo 16 for humans, xor can be aided by the use of a table for beginners (without revealing the state of calculation), and rotation can be treated as an S-box (which also can be written on a piece of paper without compromising security). The constant rotates in the middle of the round are designed to 'offset' the bitstring from each other, in an attempt to make the output less linear (using actual S-boxes, such as 4-bit optimal S-boxes, proved risky, because it appears to be very difficult to design a good S-box which will not result in some weird pattern / loop in such a construction - especially for 4 bits).

The main design was allowing a human to work with at most (around) 3 numbers at any given time (not including the key, which would be memorized), allowing a trained human to perform calculations in his/her head. To compensate for this, there is a large number of rounds involved to introduce more security.

### Posting attacks / reporting issues

If you found some kind of attack (even marginally efficient compared to pure brute-force), feel free to reply on reddit (if it is catastrophical) or raise an issue here. I created this because I couldn't find anything like this before, and I don't expect attempt #1 to be strong
