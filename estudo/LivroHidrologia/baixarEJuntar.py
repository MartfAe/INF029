import requests
import os
from PIL import Image

os.makedirs("paginas_livro", exist_ok=True)

total_paginas = 5
base_url = "https://livros.abrhidro.org.br/ha3/files/page/"

imagens = []

for i in range(1, total_paginas + 1):
    url = f"{base_url}{i}.jpg"
    nome_arquivo = f"paginas_livro/pagina_{i:03}.jpg"

    resposta = requests.get(url)
    if resposta.status_code == 200:
        with open(nome_arquivo, "wb") as f:
            f.write(resposta.content)
        print(f"[OK] Página {i} baixada.")
    else:
        print(f"[ERRO] Falha ao baixar página {i}")

    try:
        img = Image.open(nome_arquivo).convert("RGB")
        imagens.append(img)
    except:
        print(f"[AVISO] Erro ao abrir página {i}, pulando...")

if imagens:
    imagens[0].save("livro_hidrologia_ambiental.pdf", save_all=True, append_images=imagens[1:])
    print("[SUCESSO] PDF final criado com sucesso!")
else:
    print("[FALHA] Nenhuma imagem válida encontrada.")
