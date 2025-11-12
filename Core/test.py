
# Pense em como voce pode utilizar o conceito de pilhas
# para implementar as funcoes avancar, voltar e acessar_site

while True:
    proximo_site = input("url: ")
    if proximo_site == ">":
        avancar()
    elif proximo_site == "<":
        voltar()
    elif proximo_site == "sair":
        print("Saindo do navegador.")
        break
    else:
        acessar_site()