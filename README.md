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

`A81C790E3EA5284A760ED287970043DC8222EE495D24B2241E4AED7D8843B885D51DA028DE8819E6E69D558140D0CB2208DDB80482508E999FD822B8D3A4A61D59FBA82E2840424E06C48262435F489E2205AEF94286C2D84701FF073219C277D55EDAB313428DDD4878670DAEA484E39278DC1E6D7FD5280EAF2A42D5ADE3E0`

Running `./human4b --hex 1000000000001` gives output:

`DC2BADA07053FC2EA0A2A2E26478270CC93D0032A04894D2536F21A5286A1C8A0F5A5A380FCC5B04026053C5DA045924AC05187DE4FAC3DDF70C351E4C585D555F21E820DC6A6920E25EC4096C392C6093A35076D3C0BD1C8AA2997D792D5D2409FF5D1727E5CA00284C4DA2E0DD23A7624CA5200529A39EA0579D22AA500CF0`

Running `./human4b --hex FFFF0000FFFF0000FFFF0000F` gives output:

`DA9F2E09D91E5041D89C05C2ACA3C3A04A939313A689A93C95C1859910CEBD52A9975B0905028549D805882B59DD65148F84DCACB304135A94D9EC98B25973341370098FAF3139939AE33D55C48D8379D8759D06699E9CA5599989CA90427150CD034A66394A2942D39A5F54938535399A299A2114135ACB7C1ADABAF448B210
`

## For analysis
### Round design diagram

The total high-level process of key generation (described as a diagram) can be found [here](https://www.draw.io/?lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Key%20stream%20generation#R3Vpbc9soFP41fkxHgK6PcZLuzmx3ttM8bPpIbGyxwUKLUG3vr1%2BwQDcc160tWdPO1BEfiMs53wfnYM%2FQw2b3m8B5%2BidfEjaD3nI3Q48zCOMoVJ8a2FeAD2AFrAVdVhBogGf6HzGgZ9CSLknRaSg5Z5LmXXDBs4wsZAfDQvBtt9mKs%2B6oOV4TB3heYOaif9OlTM2yYNTgvxO6Tu3IIEyqmle8eFsLXmZmvBlEq8O%2FqnqDbV9moUWKl3zbgtDTDD0IzmX1tNk9EKZNa81Wvffxndp63oJk8pwXjFu%2BYVaapcd3r1QeTFtmkggzTbm3pjksjujXvRmab1MqyXOOF7p2q7igsFRumCoB9Wh6J0KS3bszBPW6FZ0I3xAp9qqJfQEZUxkq2eK28QsMDZa2fGIxbKiwrntuzKEejEWOWyd2Vk%2BWiiemyIVM%2BZpnmD016Lxrn5YtyI7KFw1%2FCEzpq63J1LyqKuCHFvhqujgUPhNB1fSVPyrwHyLl3ugGl5IrqJnOJ87zjgP0rE%2BbXy2Sl2JhWiEjOSzWxJrzuJMEYVjSb93eLzE5cgj5kYpCE9LX8qKymBwjAXQpWWPXpmQyDiXP5VeLukGfuD%2FHPf%2F63DOvfuY0k40bUc%2BN0Ou5p5qCeavx0L0QeN9qlusGxalxgi5dYq%2Fn8KrHxv31Gs9ihO8o5hOelmBgdEPB2MhjxE089pO2Fu68Dx5Ct9nJg4HU9KMi8KN4UBEEjgj%2BIHp%2Bs2Cu%2Fj%2FeXAI%2B8M%2BQQDiQBKJhJABPaMA5DYbleejyHNyE6CDph6vXJXqdOIy3nU3AlcmFrjxXKTb8vLZ1o0mbt8oCxz8SokGVEjpHAtLlL9pbt4%2BJ%2BkkE9N0DwQdDxUTDJLYtjrdo%2FdKmfFM3LMvBkRT24gPhbPO6SWwdjYApRCNhLyBH4ZFoxB%2BIfLW7fl3yHclhRzvCgJsP1uSDUySfH49JPv%2BXJ9%2BRlO%2FiA%2F5s8p3Iw9AUyReCMcl3g%2FvkMO5fRahs8CZXEeBY5BlcSMyfy9HipLsDoetGnsANPV%2F%2B%2BuL6njGaF%2BT7vMdFXn3JtaI7zYSrxJ9BLwQIXCHER3QQX0MHA91HnEqy1MZ%2F%2B%2B9VQDKABM7em5PpsxIm3btyPxqRleHorIyjyezOVYgwhd25jgftEX3lq2K70inrwEfdu5HQG1EHbgw3qYsT2KVHNObFCXT30BkMmRphvuIHEjeWCf8tua24Kw66vVcNIMp3TaV6Wuu%2Fj1xrL6XKvl6ZSaoH3RKttTJTn7zUffOV%2Bng7xNMbrDYGipkd%2FVXYniyillJNycI9vykPyK5zCin4G3ngjOstJ%2BOZJv%2BKMtaDMKPrTBUX5PADETTX%2FqQLzO5NxYYul%2Bw95XT5cg1CxN2vVuIjhIAxdAlRM%2BkHGKGKzY9zqs2n%2BQEUevof).

The round design digram I have created (in probably pretty readable form), and it can be seen [here](https://www.draw.io/?lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=Untitled%20Diagram.xml#R7Zpdb5swFIZ%2FTS43YTt8XW5d9yFtqrRerL10gwNsBDNiGrJfPwMGYux01ZrYEWovKnxsbPzyvIRjvEBXm%2FpTiYvkG41ItoBOVC%2FQhwWEge%2Fx%2F01g3wWWAHaBuEyjLgTGwG36h4igI6JVGpGt1JBRmrG0kIMrmudkxaQYLku6k5utaSaPWuCYKIHbFc7U6I80YomYFvTH%2BGeSxkk%2FMvDCruYBr37FJa1yMd4ConX711VvcN%2BXmOg2wRHdHYTQ9QJdlZSy7mhTX5GskbaXrTvv45Ha4bpLkrPnnCDu05bt%2B6mTiCshirRkCY1pjrPrMfq%2BnR5pOnB4KWGbjB8CfkjqlN014beuKN33NTkr9wdVTfFedPCTMLYXCOCKUR4ax%2F1KaSH66K60ubyjcxWhLa3KlWgluGO4jIlo5Q46c3wJ3RB%2BMbxJSTLM0ke5dyxAiod2o5j8QOip11YM%2FYizSnT6JS8qxkNAUV3WdJekjNwWuJ3EjjtM1ln0S0pG6qe1UGfZn%2BAIAIVBkSjuRtpBz2hyQLrnvFwX3zBzQCKubXde5pA95oCK1swMrRE3NCQuOmpoaN3QCNkzNFCnPzNHL%2B1BB9y5O1ojLkCG1F0etTSybmnXtWjppWnqTFvatUgdnP2vtE5dz5C6ruLpu5vvquBZxrNJ8m8n423RpZjrtG7kP8nrN5StDQLV24HG2sEJrD2knrOFL9TA5xuCL7x8%2BNDkdwUahA%2BEc4cPaBIUEBiiD6gpysXh5%2FqT15rQ4LNv9i%2FTwFPxg9AUfp6C3wJ6eNNQFbN2Tk%2BVLmFdbPLD7Ib%2Bs%2BDswXoRnKYXY42n0cC3CKfxdUfz3tfJayqn6Qf%2FX%2B%2Fbz7en70VGvR%2FM3vuBRTjR7HMerbxLU94PXuZ9aN3705dSo943nhOZ9j6EFuFEKl0z875OXnSE99O%2FVkGd97PG2Q%2F8oDd8G1jTnEl3wvtd0b7izbbV513zPIBFPVaOvQwd8Yvq%2BpL75%2BGDMW2nEsiVHim%2Br%2Ba5ruaRsjxBnouML98bZ16zzIKMrd%2BryyyvzLd3wJOZDzTfrM7G%2FPz3Mmm%2BlCJju5nUT6WvzLc8BzLzoWOQeaDclJuKXeomM%2BC4qjRn%2B4SN1If0oI39hGO6X8ewNuo30kEb%2Bwsx040PZ9WGF8fttm3dwZZmdP0X). All calculations work with 4-bit numbers. The other thing is I tried making the round function in the code readable, so if you prefer that feel free.

### Dieharder
Latest `dieharder` tests can be found in [dieharder.txt](dieharder.txt).

### Reasoning about security

I do not personally think this will turn out to be a strong PRNG, but on the basics the output (and diffusion) appears to be alright, and distribution/dieharder works pretty well.

### Design ideas

The 3 operations `+`, `xor` and `>>>` (right rotate) were chosen because addition is easy to compute modulo 16 for humans, xor can be aided by the use of a table for beginners (without revealing the state of calculation), and rotation can be treated as an S-box (which also can be written on a piece of paper without compromising security). The constant rotates in the middle of the round are designed to 'offset' the bitstring from each other, in an attempt to make the output less linear (using actual S-boxes, such as 4-bit optimal S-boxes, proved risky, because it appears to be very difficult to design a good S-box which will not result in some weird pattern / loop in such a construction - especially for 4 bits).

The main design was allowing a human to work with at most (around) 3 numbers at any given time (not including the key, which would be memorized), allowing a trained human to perform calculations in his/her head. To compensate for this, there is a large number of rounds involved to introduce more security.

### Posting attacks / reporting issues

If you found some kind of attack (even marginally efficient compared to pure brute-force), feel free to reply on reddit (if it is catastrophical) or raise an issue here. I created this because I couldn't find anything like this before, and I don't expect attempt #1 to be strong, not only that I myself have found some iffy points that I suspect will turn into (even perhaps practical) attacks, which some of you will no doubt find.

