object cfgWindow: TcfgWindow
  Left = 0
  Top = 0
  BorderStyle = bsSizeToolWin
  Caption = 'Config'
  ClientHeight = 225
  ClientWidth = 481
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 10
    Top = 8
    Width = 463
    Height = 177
    Caption = 'Mask3x3'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object CSpinEdit1: TCSpinEdit
      Left = 16
      Top = 24
      Width = 81
      Height = 22
      TabOrder = 0
    end
    object CSpinEdit2: TCSpinEdit
      Left = 103
      Top = 24
      Width = 82
      Height = 22
      TabOrder = 1
    end
    object CSpinEdit3: TCSpinEdit
      Left = 191
      Top = 24
      Width = 82
      Height = 22
      TabOrder = 2
    end
    object CSpinEdit4: TCSpinEdit
      Left = 279
      Top = 24
      Width = 81
      Height = 22
      TabOrder = 3
    end
    object CSpinEdit5: TCSpinEdit
      Left = 366
      Top = 24
      Width = 82
      Height = 22
      TabOrder = 4
    end
    object CSpinEdit6: TCSpinEdit
      Left = 15
      Top = 52
      Width = 82
      Height = 22
      TabOrder = 5
    end
    object CSpinEdit7: TCSpinEdit
      Left = 103
      Top = 52
      Width = 81
      Height = 22
      TabOrder = 6
    end
    object CSpinEdit8: TCSpinEdit
      Left = 190
      Top = 52
      Width = 82
      Height = 22
      TabOrder = 7
    end
    object CSpinEdit9: TCSpinEdit
      Left = 278
      Top = 52
      Width = 82
      Height = 22
      TabOrder = 8
    end
    object CSpinEdit10: TCSpinEdit
      Left = 366
      Top = 52
      Width = 82
      Height = 22
      TabOrder = 9
    end
    object CSpinEdit11: TCSpinEdit
      Left = 15
      Top = 80
      Width = 82
      Height = 22
      TabOrder = 10
    end
    object CSpinEdit12: TCSpinEdit
      Left = 103
      Top = 80
      Width = 82
      Height = 22
      TabOrder = 11
    end
    object CSpinEdit13: TCSpinEdit
      Left = 191
      Top = 80
      Width = 82
      Height = 22
      TabOrder = 12
    end
    object CSpinEdit14: TCSpinEdit
      Left = 278
      Top = 80
      Width = 82
      Height = 22
      TabOrder = 13
    end
    object CSpinEdit15: TCSpinEdit
      Left = 366
      Top = 80
      Width = 82
      Height = 22
      TabOrder = 14
    end
    object CSpinEdit16: TCSpinEdit
      Left = 15
      Top = 108
      Width = 82
      Height = 22
      TabOrder = 15
    end
    object CSpinEdit17: TCSpinEdit
      Left = 103
      Top = 108
      Width = 82
      Height = 22
      TabOrder = 16
    end
    object CSpinEdit18: TCSpinEdit
      Left = 191
      Top = 108
      Width = 82
      Height = 22
      TabOrder = 17
    end
    object CSpinEdit19: TCSpinEdit
      Left = 278
      Top = 108
      Width = 82
      Height = 22
      TabOrder = 18
    end
    object CSpinEdit20: TCSpinEdit
      Left = 366
      Top = 108
      Width = 82
      Height = 22
      TabOrder = 19
    end
    object CSpinEdit21: TCSpinEdit
      Left = 15
      Top = 136
      Width = 82
      Height = 22
      TabOrder = 20
    end
    object CSpinEdit22: TCSpinEdit
      Left = 103
      Top = 136
      Width = 82
      Height = 22
      TabOrder = 21
    end
    object CSpinEdit23: TCSpinEdit
      Left = 190
      Top = 136
      Width = 82
      Height = 22
      TabOrder = 22
    end
    object CSpinEdit24: TCSpinEdit
      Left = 279
      Top = 136
      Width = 82
      Height = 22
      TabOrder = 23
    end
    object CSpinEdit25: TCSpinEdit
      Left = 367
      Top = 136
      Width = 82
      Height = 22
      TabOrder = 24
    end
  end
  object OK: TButton
    Left = 143
    Top = 191
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 1
    OnClick = OKClick
  end
  object Cancel: TButton
    Left = 232
    Top = 191
    Width = 75
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 2
    OnClick = CancelClick
  end
end
