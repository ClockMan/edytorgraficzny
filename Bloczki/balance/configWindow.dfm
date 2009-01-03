object cfgWin: TcfgWin
  Left = 392
  Top = 292
  BorderStyle = bsToolWindow
  Caption = 'Balance'
  ClientHeight = 199
  ClientWidth = 280
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 265
    Height = 185
    Caption = 'Balans kolor'#243'w'
    TabOrder = 0
    object OK: TButton
      Left = 48
      Top = 147
      Width = 65
      Height = 25
      Caption = 'OK'
      TabOrder = 0
      OnClick = OKClick
    end
    object poziomR: TTrackBar
      Left = 32
      Top = 16
      Width = 169
      Height = 45
      Max = 255
      Min = -255
      TabOrder = 1
      OnChange = poziomRChange
    end
    object poziomRShow: TEdit
      Left = 208
      Top = 18
      Width = 41
      Height = 21
      TabOrder = 2
      OnChange = poziomRShowChange
    end
    object Cancel: TButton
      Left = 144
      Top = 147
      Width = 57
      Height = 25
      Caption = 'Anuluj'
      TabOrder = 3
      OnClick = CancelClick
    end
    object poziomG: TTrackBar
      Left = 32
      Top = 56
      Width = 169
      Height = 45
      Max = 255
      Min = -255
      TabOrder = 4
      OnChange = poziomGChange
    end
    object poziomB: TTrackBar
      Left = 32
      Top = 96
      Width = 169
      Height = 45
      Max = 255
      Min = -255
      TabOrder = 5
      OnChange = poziomBChange
    end
    object poziomGShow: TEdit
      Left = 208
      Top = 58
      Width = 41
      Height = 21
      TabOrder = 6
      OnChange = poziomGShowChange
    end
    object poziomBShow: TEdit
      Left = 208
      Top = 98
      Width = 41
      Height = 21
      TabOrder = 7
      OnChange = poziomBShowChange
    end
    object R: TStaticText
      Left = 8
      Top = 16
      Width = 17
      Height = 28
      Caption = 'R'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 8
    end
    object G: TStaticText
      Left = 8
      Top = 56
      Width = 18
      Height = 28
      Caption = 'G'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 9
    end
    object B: TStaticText
      Left = 8
      Top = 96
      Width = 16
      Height = 28
      Caption = 'B'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 10
    end
  end
end
