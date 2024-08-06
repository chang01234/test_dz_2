import code_gen

def run_code_gen():
    code_gen.main()


def main():
    print("Prebuild steps:")
    print("  -> Run code generation")
    run_code_gen()
    print("Prebuild complete")


main()
