from fpdf import FPDF
import sys  # Remova o 'os' pois não é mais necessário

def txt_para_pdf(txt_path, pdf_path):
    pdf = FPDF()
    pdf.add_page()
    pdf.set_auto_page_break(auto=True, margin=15)
    pdf.set_font("Arial", size=12)

    try:
        with open(txt_path, "r", encoding="utf-8") as f:
            for linha in f:
                linha = linha.strip()
                pdf.multi_cell(0, 10, txt=linha)
        pdf.output(pdf_path)
        print(f"PDF gerado: {pdf_path}")
        return True
    except Exception as e:
        print(f"Erro ao gerar PDF: {e}")
        return False

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Uso: python gerar_pdf.py <arquivo_txt> <arquivo_pdf>")
        sys.exit(1)
    
    txt_file = sys.argv[1]
    pdf_file = sys.argv[2]
    txt_para_pdf(txt_file, pdf_file)